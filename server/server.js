const express = require('express');
const sqlite3 = require('sqlite3').verbose();
const cors = require('cors');
const path = require('path');

const app = express();
app.use(cors());
app.use(express.json());
app.use(express.static('public'));

const db = new sqlite3.Database('./keys.db', (err) => {
    if (err) console.error(err.message);
    else console.log('Connected to SQLite DB.');
});

db.run(`CREATE TABLE IF NOT EXISTS keys (
    key TEXT PRIMARY KEY,
    createdAt DATETIME DEFAULT CURRENT_TIMESTAMP,
    expiresAt DATETIME
)`);

// Admin login logic
const ADMIN_PASS = 'admin123';

app.post('/api/admin/login', (req, res) => {
    const { password } = req.body;
    if (password === ADMIN_PASS) {
        res.json({ success: true, token: 'fake-jwt-token' });
    } else {
        res.status(401).json({ success: false, message: 'Invalid password' });
    }
});

// Create key
app.post('/api/admin/keys', (req, res) => {
    const { token, key, days } = req.body;
    if (token !== 'fake-jwt-token') return res.status(401).json({ error: 'Unauthorized' });

    let expiresAt = null;
    if (days && days > 0) {
        const date = new Date();
        date.setDate(date.getDate() + parseInt(days));
        expiresAt = date.toISOString();
    }

    db.run(`INSERT INTO keys (key, expiresAt) VALUES (?, ?)`, [key, expiresAt], function(err) {
        if (err) return res.status(500).json({ error: err.message });
        res.json({ success: true, key, expiresAt });
    });
});

// List keys
app.get('/api/admin/keys', (req, res) => {
    const { token } = req.query;
    if (token !== 'fake-jwt-token') return res.status(401).json({ error: 'Unauthorized' });

    db.all(`SELECT * FROM keys ORDER BY createdAt DESC`, [], (err, rows) => {
        if (err) return res.status(500).json({ error: err.message });
        res.json(rows);
    });
});

// Delete key
app.delete('/api/admin/keys/:key', (req, res) => {
    const { token } = req.query;
    if (token !== 'fake-jwt-token') return res.status(401).json({ error: 'Unauthorized' });

    db.run(`DELETE FROM keys WHERE key = ?`, [req.params.key], function(err) {
        if (err) return res.status(500).json({ error: err.message });
        res.json({ success: true });
    });
});

// Client API to verify
app.get('/api/verify', (req, res) => {
    const { key } = req.query;
    if (!key) return res.json({ valid: false, message: 'No key provided' });

    db.get(`SELECT * FROM keys WHERE key = ?`, [key], (err, row) => {
        if (err) return res.json({ valid: false, message: 'Database error' });
        if (!row) return res.json({ valid: false, message: 'Invalid Key' });

        if (row.expiresAt) {
            const exp = new Date(row.expiresAt);
            const now = new Date();
            if (now > exp) {
                return res.json({ valid: false, message: 'Key expired' });
            }
        }
        res.json({ valid: true, message: 'Authenticated' });
    });
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
