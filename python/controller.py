from gpiozero import LED, Button
import time
import os
html_header = """
<html>
<head>
<title> Plant Dashboard </title>
<meta http-equiv="refresh" content="3">
</head>
<body>
"""
html_footer = """
</body>
</html>
"""

soil_wet_sensor = Button(2)
check_soil_wet_sensor = Button(3)
runoff_wet_sensor = Button(4)
ph_sensor = Button(21)

soil_status = ""
soil_check_status = ""
runoff_status = ""
pH_status = ""

while True:
    html_payload = html_header
    if not soil_wet_sensor.is_pressed:
        soil_status = "<p style=\"color:red;\">Soil is dry!</p>"
    elif soil_wet_sensor.is_pressed:
        soil_status = "<p style=\"color:green;\">Soil is wet!</p>"
    
    if not check_soil_wet_sensor.is_pressed:
        soil_check_status = "<p style=\"color:red;\">Check soil for drying.</p>"
    elif check_soil_wet_sensor.is_pressed:
        soil_check_status = "<p style=\"color:green;\">No need to check for drying.</p>"
    if not runoff_wet_sensor.is_pressed:
        runoff_status = "<p style=\"color:red;\">Runoff is present!</p>"
    elif runoff_wet_sensor.is_pressed:
        runoff_status = "<p style=\"color:green;\">No Runoff is present!</p>"

    if not ph_sensor.is_pressed:
        pH_status = "<p style=\"color:red;\">pH is out of range!</p>"
    elif ph_sensor.is_pressed:
        pH_status = "<p style=\"color:green;\">pH is in range!</p>"
    html_payload += soil_status + "<br>"
    html_payload += soil_check_status + "<br>"
    html_payload += runoff_status + "<br>"
    html_payload += pH_status
    html_payload += html_footer
    fp = open("index.html", "w")
    fp.write(html_payload)
    fp.close()
    time.sleep(2)
