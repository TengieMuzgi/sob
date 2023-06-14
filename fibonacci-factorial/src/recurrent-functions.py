import requests
import sys

def factorial_recursive(n):
    if n == 0:
        return 1
    return n * factorial_recursive(n - 1)

def fibonacci_recursive(n):
    if n <= 1:
        return n
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2)

function_type = sys.argv[1]
number = int(sys.argv[2])

if function_type not in ["factorial", "fibonacci"] or not number:
    print("Niepoprawne parametry. Użyj: python recurrent-functions.py [factorial|fibonacci] [liczba]")
    sys.exit(1)

result = None
if function_type == "factorial":
    result = factorial_recursive(number)
elif function_type == "fibonacci":
    result = fibonacci_recursive(number)

def send_data():
    try:
        response = requests.post(f"http://localhost:3333/{function_type}", json={"result": result})
        print(response.json())
    except requests.exceptions.RequestException as error:
        print("Wystąpił błąd podczas wysyłania żądania:", error)

send_data()