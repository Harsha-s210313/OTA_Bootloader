from flask import Flask, send_file
from firmware import load_firmware
from crypto import sign_firmware, compute_hash
import io

app = Flask(__name__)

# Load everything once at startup
firmware_data = load_firmware("firmware.bin")
firmware_hash = compute_hash(firmware_data)
signature = sign_firmware(firmware_data)

@app.route("/hash")
def serve_hash():
    return send_file(io.BytesIO(firmware_hash), mimetype='application/octet-stream')

@app.route("/signature")
def serve_signature():
    return send_file(io.BytesIO(signature), mimetype='application/octet-stream')

@app.route("/firmware")
def serve_firmware():
    return send_file(io.BytesIO(firmware_data), mimetype='application/octet-stream')

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)