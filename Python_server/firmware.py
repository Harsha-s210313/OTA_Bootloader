def load_firmware(firmware_path):
    with open(firmware_path, "rb") as f:
        firmware_data = f.read()
    return firmware_data