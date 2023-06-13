const axios = require("axios");

function factorialRecursive(n) {
  if (n === 0) {
    return 1;
  }
  return n * factorialRecursive(n - 1);
}

function fibonacciRecursive(n) {
  if (n <= 1) {
    return n;
  }
  return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

const functionType = process.argv[2];
const number = parseInt(process.argv[3]);

if (!["factorial", "fibonacci"].includes(functionType) || isNaN(number)) {
  console.error(
    "Niepoprawne parametry. Użyj: node recurrent-functions.js [factorial|fibonacci] [liczba]"
  );
  process.exit(1);
}

let result;
if (functionType === "factorial") {
  result = factorialRecursive(number);
} else if (functionType === "fibonacci") {
  result = fibonacciRecursive(number);
}

const sendData = async () => {
  try {
    const response = await axios.post(`http://localhost:3333/${functionType}`, {
      result: result,
    });
    console.log(response.data);
  } catch (error) {
    console.error("Wystąpił błąd podczas wysyłania żądania:", error);
  }
};

sendData();
