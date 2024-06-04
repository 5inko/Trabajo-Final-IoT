# coap_client.py
import subprocess

def send_coap_message(command, intensity=None):
    esp32_ip_address = "192.168.25.159"
    uri = f"coap://{esp32_ip_address}/light"
    
    if intensity is not None:
        payload = f"{command}{intensity}"
    else:
        payload = command
    
    coap_command = ["coap-client", "-e", payload, "-m", "put", uri]
    
    try:
        result = subprocess.run(coap_command, capture_output=True, text=True)
        print(f"Result: {result.stdout}")
    except Exception as e:
        print(f"Failed to fetch resource: {e}")