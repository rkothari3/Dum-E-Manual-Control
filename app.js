// Serial port connection state
let port;
let writer;

// DOM elements
const connectBtn = document.getElementById('connectBtn');
const resetBtn = document.getElementById('resetBtn');
const status = document.getElementById('status');
const sliders = [];
const values = [];

// Servo control key mappings: [decrease, increase]
const keyMaps = [
    ['q', 'w'],  // Base Swivel
    ['a', 's'],  // Base Up/Down
    ['z', 'x'],  // Arm Big
    ['e', 'r'],  // Arm Small
    ['d', 'f'],  // Gripper Up/Down
    ['c', 'v']   // Gripper Open/Close
];

// Serial communication
async function connect() {
    try {
        port = await navigator.serial.requestPort();
        await port.open({ baudRate: 115200 });
        writer = port.writable.getWriter();

        connectBtn.textContent = 'DISCONNECT';
        status.textContent = 'ONLINE';
        status.className = 'connected';
        resetBtn.disabled = false;

        // Enable sliders
        for (let i = 1; i <= 6; i++) {
            sliders[i].disabled = false;
        }
    } catch (error) {
        alert('Failed to connect: ' + error.message);
    }
}

async function disconnect() {
    try {
        if (writer) {
            writer.releaseLock();
        }
        await port.close();
        port = null;
        writer = null;

        connectBtn.textContent = 'CONNECT';
        status.textContent = 'OFF';
        status.className = 'disconnected';
        resetBtn.disabled = true;

        // Disable sliders
        for (let i = 1; i <= 6; i++) {
            sliders[i].disabled = true;
        }
    } catch (error) {
        console.error('Disconnect error:', error);
    }
}

async function sendCommand(key) {
    if (writer) {
        const encoder = new TextEncoder();
        await writer.write(encoder.encode(key));
    }
}

// Slider control
function initializeSliders() {
    for (let i = 1; i <= 6; i++) {
        sliders[i] = document.getElementById(`servo${i}`);
        values[i] = document.getElementById(`value${i}`);

        let prevValue = 90;
        sliders[i].addEventListener('input', async (e) => {
            const newValue = parseInt(e.target.value);
            values[i].textContent = newValue + '°';

            if (writer && newValue !== prevValue) {
                const key = newValue > prevValue ? keyMaps[i-1][1] : keyMaps[i-1][0];
                await sendCommand(key);
            }
            prevValue = newValue;
        });
    }
}

// Reset functionality
async function resetServos() {
    if (writer) {
        await sendCommand('0');
        // Reset all sliders to center
        for (let i = 1; i <= 6; i++) {
            sliders[i].value = 90;
            values[i].textContent = '90°';
        }
    }
}

// Keyboard control
function handleKeyPress(e) {
    if (!writer) return;

    const key = e.key.toLowerCase();
    const validKeys = ['q', 'w', 'a', 's', 'z', 'x', 'e', 'r', 'd', 'f', 'c', 'v', '0'];

    if (validKeys.includes(key)) {
        e.preventDefault();
        sendCommand(key);

        // Update slider position based on key pressed
        if (key !== '0') {
            for (let i = 0; i < 6; i++) {
                if (key === keyMaps[i][0]) {
                    // Decrease
                    const newVal = Math.max(0, parseInt(sliders[i+1].value) - 5);
                    sliders[i+1].value = newVal;
                    values[i+1].textContent = newVal + '°';
                } else if (key === keyMaps[i][1]) {
                    // Increase
                    const newVal = Math.min(180, parseInt(sliders[i+1].value) + 5);
                    sliders[i+1].value = newVal;
                    values[i+1].textContent = newVal + '°';
                }
            }
        } else {
            // Reset to center
            for (let i = 1; i <= 6; i++) {
                sliders[i].value = 90;
                values[i].textContent = '90°';
            }
        }
    }
}

// Event listeners
function initializeEventListeners() {
    connectBtn.addEventListener('click', async () => {
        if (port) {
            await disconnect();
        } else {
            await connect();
        }
    });

    resetBtn.addEventListener('click', resetServos);
    document.addEventListener('keydown', handleKeyPress);
}

// Initialize on page load
document.addEventListener('DOMContentLoaded', () => {
    initializeSliders();
    initializeEventListeners();
});
