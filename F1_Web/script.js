// Database State (seperti ListTeam L)
let teams = JSON.parse(localStorage.getItem('f1Data')) || [];

// Utama

// Fungsi hitungPoin dari f1.cpp
function hitungPoin(posisi, penalti) {
    let poinDasar = 0;
    if (posisi === 1) poinDasar = 25;
    else if (posisi === 2) poinDasar = 18;
    else if (posisi === 3) poinDasar = 15;
    else if (posisi === 4) poinDasar = 12;
    else if (posisi === 5) poinDasar = 10;
    else if (posisi === 6) poinDasar = 8;
    else if (posisi === 7) poinDasar = 6;
    else if (posisi === 8) poinDasar = 4;
    else if (posisi === 9) poinDasar = 2;
    else if (posisi === 10) poinDasar = 1;
    else poinDasar = 0;

    let poinAkhir = poinDasar - penalti;
    return (poinAkhir < 0) ? 0 : poinAkhir;
}

// Fungsi Statistik (totalPoints, maxPoint, minPoint, avgPoint dari f1.cpp)
function calculateStats(team) {
    if (!team.races || team.races.length === 0) {
        return { total: 0, max: 0, min: 0, avg: 0 };
    }

    let total = 0;
    let allPoints = [];

    // Mengumpulkan semua poin dari setiap race (Driver 1 & Driver 2)
    team.races.forEach(r => {
        // struct RaceStat di f1.h punya poin[2]
        total += (r.poin[0] + r.poin[1]);
        allPoints.push(r.poin[0]);
        allPoints.push(r.poin[1]);
    });

    // Menghindari Math.max/min pada array kosong jika poin 0
    if (allPoints.length === 0) allPoints = [0];

    return {
        total: total,
        max: Math.max(...allPoints),
        min: Math.min(...allPoints),
        avg: (total / allPoints.length).toFixed(1)
    };
}

// Render Function
function renderTeams() {
    const grid = document.getElementById('teamGrid');
    const search = document.getElementById('searchInput').value.toLowerCase();
    grid.innerHTML = '';

    teams.forEach((team, index) => {
        if (team.namaTeam.toLowerCase().includes(search)) {
            const stats = calculateStats(team);
            
            // HTML struktur mirip f1.h (Team Info + Race List)
            const div = document.createElement('div');
            div.className = 'card';
            div.innerHTML = `
                <div class="card-actions">
                    <button class="icon-btn" onclick="editTeam(${index})"><i class="fa-solid fa-pen"></i></button>
                    <button class="icon-btn del" onclick="deleteTeam(${index})"><i class="fa-solid fa-trash"></i></button>
                </div>
                <div class="card-header">
                    <div>
                        <h3>${team.namaTeam}</h3>
                        <small>${team.negaraAsal} (${team.tahunBerdiri})</small>
                    </div>
                </div>
                <div class="badges">
                    ${team.noDriver.map(d => `<span class="badge drv">#${d}</span>`).join('')}
                    ${team.warnaLivery.map(c => `<span class="badge liv">${c}</span>`).join('')}
                </div>
                
                <div class="stats-box">
                    <div><span class="stat-val">${stats.total}</span><span class="stat-lbl">Total</span></div>
                    <div><span class="stat-val">${stats.avg}</span><span class="stat-lbl">Avg</span></div>
                    <div><span class="stat-val">${stats.max}</span><span class="stat-lbl">Max</span></div>
                    <div><span class="stat-val">${stats.min}</span><span class="stat-lbl">Min</span></div>
                </div>

                <div class="race-list">
                    <strong>Riwayat Race:</strong>
                    ${team.races.map((r, rIdx) => `
                        <div class="race-item" onclick="deleteRace(${index}, ${rIdx})" title="Klik untuk hapus race ini">
                            <span>S${r.noBalapan} ${r.namaSirkuit}</span>
                            <span>Poin: ${r.poin[0] + r.poin[1]}</span>
                        </div>
                    `).join('')}
                    ${team.races.length === 0 ? '<p>Belum ada data.</p>' : ''}
                </div>

                <button class="action-btn" onclick="openRaceModal(${index})">+ Input Race</button>
            `;
            grid.appendChild(div);
        }
    });
    localStorage.setItem('f1Data', JSON.stringify(teams));
}

function renderStandings(order) {
    const tbody = document.querySelector('#standingsTable tbody');
    tbody.innerHTML = '';

    // Sorting seperti di main.cpp (menu 9) dan f1.cpp
    let sortedTeams = [...teams].sort((a, b) => {
        let ptsA = calculateStats(a).total;
        let ptsB = calculateStats(b).total;
        return order === 'desc' ? ptsB - ptsA : ptsA - ptsB;
    });

    sortedTeams.forEach((team, i) => {
        const stats = calculateStats(team);
        const row = `
            <tr>
                <td>${i + 1}</td>
                <td><strong>${team.namaTeam}</strong></td>
                <td>${team.negaraAsal}</td>
                <td style="color:var(--blue); font-weight:bold;">${stats.total}</td>
                <td>Max: ${stats.max} / Min: ${stats.min}</td>
            </tr>
        `;
        tbody.innerHTML += row;
    });
}

// CRUD

// Add/Edit Team
document.getElementById('teamForm').addEventListener('submit', (e) => {
    e.preventDefault();
    const idx = document.getElementById('editIndex').value;
    
    const teamData = {
        namaTeam: document.getElementById('namaTeam').value,
        negaraAsal: document.getElementById('negaraAsal').value,
        tahunBerdiri: parseInt(document.getElementById('tahunBerdiri').value),
        noDriver: [
            document.getElementById('noDriver1').value,
            document.getElementById('noDriver2').value
        ],
        warnaLivery: [
            document.getElementById('livery1').value,
            document.getElementById('livery2').value,
            document.getElementById('livery3').value
        ],
        // Jika edit, pertahankan races yang sudah ada. Jika baru, array kosong.
        races: idx != -1 ? teams[idx].races : [] 
    };

    if (idx != -1) {
        teams[idx] = teamData; // Update
    } else {
        teams.push(teamData); // Add New
    }
    
    closeModal('teamModal');
    renderTeams();
    renderStandings('desc');
});

// Add Race (Sesuai RaceStat di f1.h dengan 2 driver)
document.getElementById('raceForm').addEventListener('submit', (e) => {
    e.preventDefault();
    const teamIdx = document.getElementById('raceTeamIndex').value;
    
    // Input
    const pos1 = parseInt(document.getElementById('pos1').value);
    const pen1 = parseInt(document.getElementById('pen1').value);
    const pos2 = parseInt(document.getElementById('pos2').value);
    const pen2 = parseInt(document.getElementById('pen2').value);

    // Hitung poin pakai fungsi dari f1.cpp
    const poin1 = hitungPoin(pos1, pen1);
    const poin2 = hitungPoin(pos2, pen2);

    const newRace = {
        noBalapan: parseInt(document.getElementById('noBalapan').value),
        namaSirkuit: document.getElementById('namaSirkuit').value,
        posisi: [pos1, pos2],
        penalti: [pen1, pen2],
        poin: [poin1, poin2]
    };

    // Push ke array race (addRace)
    teams[teamIdx].races.push(newRace);
    
    closeModal('raceModal');
    renderTeams();
    renderStandings('desc');
});

// Delete
function deleteTeam(index) {
    if(confirm("Hapus tim ini?")) {
        teams.splice(index, 1);
        renderTeams();
        renderStandings('desc');
    }
}

function deleteRace(teamIdx, raceIdx) {
    if(confirm("Hapus data balapan ini?")) {
        teams[teamIdx].races.splice(raceIdx, 1);
        renderTeams();
        renderStandings('desc');
    }
}

function resetData() {
    if(confirm("Reset semua data?")) {
        localStorage.removeItem('f1Data');
        teams = [];
        renderTeams();
    }
}

// UI HELPERS
function switchTab(tab) {
    document.getElementById('dashboardView').style.display = tab === 'dashboard' ? 'block' : 'none';
    document.getElementById('standingsView').style.display = tab === 'standings' ? 'block' : 'none';
    
    // Update active class sidebar
    document.querySelectorAll('nav a').forEach(el => el.classList.remove('active'));
    event.target.closest('a').classList.add('active');
    
    if(tab === 'standings') renderStandings('desc');
}

function openModal(id) {
    document.getElementById(id).style.display = 'block';
    if(id === 'teamModal') {
        document.getElementById('teamForm').reset();
        document.getElementById('editIndex').value = -1;
        document.getElementById('teamModalTitle').innerText = "Tambah Tim Baru";
    }
}

function openRaceModal(index) {
    const team = teams[index];
    document.getElementById('raceTeamIndex').value = index;
    // Tampilkan nama driver di label agar user tau input buat siapa
    document.getElementById('lblDriver1').innerText = `Driver #${team.noDriver[0]}`;
    document.getElementById('lblDriver2').innerText = `Driver #${team.noDriver[1]}`;
    document.getElementById('raceModal').style.display = 'block';
    document.getElementById('raceForm').reset();
}

function editTeam(index) {
    const t = teams[index];
    document.getElementById('editIndex').value = index;
    document.getElementById('namaTeam').value = t.namaTeam;
    document.getElementById('negaraAsal').value = t.negaraAsal;
    document.getElementById('tahunBerdiri').value = t.tahunBerdiri;
    document.getElementById('noDriver1').value = t.noDriver[0];
    document.getElementById('noDriver2').value = t.noDriver[1];
    document.getElementById('livery1').value = t.warnaLivery[0];
    document.getElementById('livery2').value = t.warnaLivery[1];
    document.getElementById('livery3').value = t.warnaLivery[2];
    
    document.getElementById('teamModalTitle').innerText = "Edit Data Tim";
    document.getElementById('teamModal').style.display = 'block';
}

function closeModal(id) {
    document.getElementById(id).style.display = 'none';
}

// Init
renderTeams();

// LANDING PAGE LOGIC

function enterApp() {
    const landing = document.getElementById('landingPage');
    const mainApp = document.getElementById('mainApp');

    // Hilangkan Landing Page
    landing.classList.add('hide-landing');

    // Munculkan Main App dengan animasi
    // timeout sedikit agar transisi landing page jalan dulu
    setTimeout(() => {
        landing.style.display = 'none'; // Hapus dari layout setelah animasi
        
        // Reset style transform/opacity pada mainApp agar muncul normal
        mainApp.style.transform = 'scale(1)';
        mainApp.style.opacity = '1';
    }, 500);
}