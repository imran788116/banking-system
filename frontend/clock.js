// Real-Time Clock Widget for Frontend (Banking System UI)
// Add this file to your frontend and include it in your HTML

(function () {
    // Create clock element
    const clock = document.createElement("div");
    clock.id = "liveClock";

    // Style it (top-right corner by default)
    clock.style.position = "fixed";
    clock.style.top = "10px";
    clock.style.right = "10px"; // change to left:10px if needed
    clock.style.background = "#000";
    clock.style.color = "#fff";
    clock.style.padding = "10px 14px";
    clock.style.borderRadius = "8px";
    clock.style.fontFamily = "Arial, sans-serif";
    clock.style.fontSize = "14px";
    clock.style.zIndex = "9999";

    document.body.appendChild(clock);

    // Update time every second
    function updateClock() {
        const now = new Date();
        clock.innerText = now.toLocaleTimeString();
    }

    setInterval(updateClock, 1000);
    updateClock();
})();  