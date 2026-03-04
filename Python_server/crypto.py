from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives import hashes, serialization
import hashlib

def load_private_key():
    with open("private_key.pem", "rb") as f:
        private_key = serialization.load_pem_private_key(
            f.read(),
            password=None,
        )
    return private_key

def compute_hash(firmware_data):
    return hashlib.sha256(firmware_data).digest()

def sign_firmware(firmware_data):
    private_key = load_private_key()
    signature = private_key.sign(
        firmware_data,
        ec.ECDSA(hashes.SHA256())
    )
    return signature