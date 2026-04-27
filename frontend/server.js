const express = require("express");
const { exec } = require("child_process");
const cors=require("cors");
const app = express();
app.use(cors());
app.use(express.json());

// Helper function to run C++ program
function runCommand(command, res) {
    exec(command, (err, stdout, stderr) => {
        if (err) return res.send("Error running program");
        res.send(stdout);
    });
}

// Routes

app.post("/create", (req, res) => {
    const { acno, name, type, deposit } = req.body;
    runCommand(`a.exe 1 ${acno} "${name}" ${type} ${deposit}`, res);
});

app.post("/deposit", (req, res) => {
    const { acno, amount } = req.body;
    runCommand(`a.exe 2 ${acno} ${amount}`, res);
});

app.post("/withdraw", (req, res) => {
    const { acno, amount } = req.body;
    runCommand(`a.exe 3 ${acno} ${amount}`, res);
});

app.post("/balance", (req, res) => {
    const { acno } = req.body;
    runCommand(`a.exe 4 ${acno}`, res);
});

app.get("/all", (req, res) => {
    runCommand(`a.exe 5`, res);
});

app.post("/delete", (req, res) => {
    const { acno } = req.body;
    runCommand(`a.exe 6 ${acno}`, res);
});

app.post("/modify", (req, res) => {
    const { acno, name, type, deposit } = req.body;
    runCommand(`a.exe 7 ${acno} "${name}" ${type} ${deposit}`, res);
});

app.listen(3000, () => console.log("Server running on http://localhost:3000"));