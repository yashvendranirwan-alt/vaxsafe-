# server.py - VaxSafe AI & Blockchain Backend
from flask import Flask, request, jsonify
import hashlib
import time
from datetime import datetime

app = Flask(__name__)

# AI Model: Vaccine Potency Logic
potency = 100.0
last_hash = "0000000000000000"

def calculate_ai_decay(temp):
    global potency
    if temp > 8.0:
        decay = (temp - 8.0) * 0.1  # AI Logic: High temp = fast decay
        potency -= decay
    elif temp < -2.0:
        potency -= 0.5
    return max(0, round(potency, 2))

@app.route('/vaxsafe/telemetry', methods=['POST'])
def handle_data():
    global last_hash
    data = request.json
    temp = data.get("temperature")
    
    # AI Analysis
    current_health = calculate_ai_decay(temp)
    
    # Blockchain Chaining Simulation
    timestamp = str(datetime.now())
    block_data = f"{temp}{current_health}{timestamp}{last_hash}"
    new_hash = hashlib.sha256(block_data.encode()).hexdigest()
    last_hash = new_hash # Chain updated

    # Response for Dashboard
    response = {
        "status": "CRITICAL" if temp > 8.0 else "SECURE",
        "ai_health": f"{current_health}%",
        "blockchain_proof": new_hash[:16] # Pehle 16 chars demo ke liye
    }
    
    print(f"Received: {temp}C | AI Health: {current_health}% | Hash: {new_hash[:10]}...")
    return jsonify(response)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
