const express = require('express');
const mysql = require('mysql2');
const cors = require('cors');

const app = express();
app.use(cors());
app.use(express.json());

const db = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '786786', // put your mysql password
    database: 'bankdb'
});


db.connect(err => {
    if (err) {
        console.log("DB ERROR:", err);
    } else {
        console.log("MySQL Connected...");
    }
});
app.post('/create-account', (req, res) => {
    console.log("Request received:", req.body);

    const { acno, name, type, deposit } = req.body;

    const sql = `
        INSERT INTO accounts (account_no, name, type, balance, status)
        VALUES (?, ?, ?, ?, ?)
    `;

    db.query(sql, [acno, name, type, deposit, 'ACTIVE'], (err, result) => {
        if (err) {
            console.log(err);
            return res.send("Error inserting data");
        }
        res.send("Account Created Successfully ✅");
    });
});
app.post("/deposit", (req, res) => {

    const acno = Number(req.body.acno);
    const amt = Number(req.body.amt);

    if (!acno || !amt) {
        return res.status(400).send("Invalid input");
    }

    const checkSql = "SELECT status FROM accounts WHERE account_no=?";

    db.query(checkSql, [acno], (err, result) => {

        if (err) {
            console.log(err);
            return res.status(500).send("DB error");
        }

        if (result.length === 0) {
            return res.status(404).send("Account not found");
        }

        if (result[0].status === "SUSPENDED") {
            return res.status(403).send("Account suspended");
        }

        const sql = "UPDATE accounts SET balance = balance + ? WHERE account_no=?";

        db.query(sql, [amt, acno], (err2) => {

            if (err2) {
                console.log(err2);
                return res.status(500).send("Deposit failed");
            }

            res.send("Deposit successful");
        });
    });
});
app.post("/withdraw", (req, res) => {

    console.log("🔥 WITHDRAW ROUTE HIT");
    console.log("BODY:", req.body);

    const acno = Number(req.body.acno);
    const amt = Number(req.body.amt);

    if (!acno || !amt) {
        return res.status(400).send("Invalid input");
    }

    const checkSql = "SELECT balance FROM accounts WHERE account_no=?";

    db.query(checkSql, [acno], (err, result) => {

        if (err) {
            console.log(err);
            return res.status(500).send("Database error");
        }

        if (result.length === 0) {
            return res.status(404).send("Account not found");
        }

        const currentBalance = Number(result[0].balance);

        if (currentBalance < amt) {
            return res.status(400).send("Insufficient balance");
        }

        const sql = "UPDATE accounts SET balance = balance - ? WHERE account_no=?";

        db.query(sql, [amt, acno], (err2) => {

            if (err2) {
                console.log(err2);
                return res.status(500).send("Withdraw failed");
            }

            res.send("Withdraw successful ✅");
        });
    });
});
app.post("/unsuspend-account", (req, res) => {

    const { acno } = req.body;

    const sql = "UPDATE accounts SET status='ACTIVE' WHERE account_no=?";

    db.query(sql, [acno], (err, result) => {

        if (err) {
            console.log(err);
            return res.status(500).send("Error unsuspending account");
        }

        res.send("Account activated successfully");
    });
});
app.get('/all-accounts', (req, res) => {
    const sql = "SELECT * FROM accounts";

    db.query(sql, (err, result) => {
        if (err) {
            console.log(err);
            return res.send("Error fetching data");
        }
        res.json(result); // send all data
    });
});
app.post('/check-account', (req, res) => {
    const { acno } = req.body;

    const sql = "SELECT * FROM accounts WHERE account_no = ?";

    db.query(sql, [acno], (err, result) => {
        if (err) return res.send("Error");

        if (result.length > 0) {
            res.json({ exists: true });
        } else {
            res.json({ exists: false });
        }
    });
});
app.listen(5000, () => {
    console.log("Server running on http://localhost:5000");
});

  