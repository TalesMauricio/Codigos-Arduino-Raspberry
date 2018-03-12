import json
import requests
import os.path
import time
from random import *

def run_observer():
    try:
        while True:
            time.sleep(1)
            observer('medidas_tanques.txt')
    except KeyboardInterrupt:
        print("parei")

def observer(filepath):
    if os.path.isfile(filepath):
        filename = filepath.split('.')
        file_copy = filename[0] + '_copy.txt'
        os.rename(
            filepath,
            file_copy
            )

        status_code = post_register_data(read_file(file_copy))
        if status_code == 200:
            delete_file(file_copy)

def delete_file(file_name):
    if os.path.isfile(file_name):
        os.remove(file_name)

def post_register_data(post_fields):
    url = 'http://169.254.150.98:3000/feeders/register_data'
    post_request = requests.post(url, json=post_fields)
    print(post_fields)
    return post_request.status_code

def read_file(file_name):
    keys = ["network_code",
            "hora",
            "minute",
            "food_level",
            "battery_level",
            "error_code",
            "temperature",
            "ph",
            "turbidity",
            "conductivity",
            "oxigenium"]
    json_data = {}
    array_data = []
    with open(file_name, "r") as file_node:
        data = file_node.readlines()

        for line in data:
            registers = line.split()

            for index, value in enumerate(registers):
                json_data[keys[index]] = value

            array_data.append(json_data)
            json_data = {}


        file_node.close()
    request_data = {'data':array_data}
    return request_data

# ID  HORA MINUTO NIVEL(0/100) BATERIA(0/100) CODE-ERROR TEMPERATURA PH TURBIDEZ CONDUTIVIDADE OXIGENIO
def generate_data():
    with open("medidas_tanques.txt", "w") as outfile:
        for i in range(0, 100):
            outfile.write(str(randint(1, 3)) + ' '
                            + str(randint(1, 24)) + ' '
                            + str(randint(1, 60)) + ' '
                            + str(randint(0, 100)) + ' '
                            + str(randint(0, 100)) + ' '
                            + str(randint(-1, 10)) + ' '
                            + str(randint(-30, 50)) + ' '
                            + str(randint(0, 14)) + ' '
                            + str(randint(1, 100)) + ' '
                            + str(randint(1, 100)) + ' '
                            + str(randint(1, 100)) + '\n')

def main():
    run_observer()

if __name__ == "__main__":
    main()
