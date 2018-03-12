import requests
import os.path
import time
from random import randint
from decouple import config

# Example .env file
# SERVER_ADDRESS=http://127.0.0.1:3000
# SERVER_ENDPOINT=/feeders/register_data
# DEBUG=False
# INPUT_FILE_NAME=medidas_tanques

server = config('SERVER_ADDRESS', default='http://127.0.0.1:3000')
endpoint = config('SERVER_ENDPOINT', default='/feeders/register_data')
DEBUG = config('DEBUG', default=False, cast=bool)
input_file_name = config('INPUT_FILE_NAME', default='medidas_tanques')

def run_observer():
    try:
        while True:
            time.sleep(1)
            observer(input_file_name + '.txt')
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
    url = "{}{}".format(server, endpoint)
    post_request = requests.post(url, json=post_fields)
    print(post_fields)
    return post_request.status_code


def read_file(file_name):
    keys = ["network_code",
            "hora",
            "minute",
            "second",
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
    request_data = {'data': array_data}
    
    return request_data


def generate_data():
    # ID HORA MINUTO NIVEL(0/100) BATERIA(0/100)
    # CODE-ERROR PH CONDUTIVIDADE TEMPERATURA TURBIDEZ OXIGENIO
    with open(input_file_name + ".txt", "w") as outfile:
        for i in range(0, 100):
            outfile.write(
                str(randint(1, 3)) + ' ' +
                str(randint(1, 23)) + ' ' +
                str(randint(1, 59)) + ' ' +
                str(randint(0, 100)) + ' ' +
                str(randint(0, 100)) + ' ' +
                str(randint(-1, 10)) + ' ' +
                str(randint(0, 14)) + ' ' +
                str(randint(0, 100)) + ' ' +
                str(randint(-30, 50)) + ' ' +
                str(randint(0, 100)) + ' ' +
                str(randint(1, 100)) + '\n')


def main():
    if DEBUG:
        generate_data()
        print('modo debug')
        time.sleep(3)

    run_observer()


if __name__ == "__main__":
    main()
