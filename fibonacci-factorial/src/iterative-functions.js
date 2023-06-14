const axios = require("axios");

function factorialIterative(n) {
  let result = 1;
  for (let i = 2; i <= n; i++) {
    result *= i;
  }
  return result;
}

function fibonacciIterative(n) {
  if (n <= 1) {
    return n;
  }
  let a = 0;
  let b = 1;
  let temp;
  for (let i = 2; i <= n; i++) {
    temp = a + b;
    a = b;
    b = temp;
  }
  return b;
}

const functionType = process.argv[2];
const number = parseInt(process.argv[3]);

if (!["factorial", "fibonacci"].includes(functionType) || isNaN(number)) {
  console.error(
    "Niepoprawne parametry. Użyj: node iterative-functions.js [factorial|fibonacci] [liczba]"
  );
  process.exit(1);
}

let result;
if (functionType === "factorial") {
  result = factorialIterative(number);
} else if (functionType === "fibonacci") {
  result = fibonacciIterative(number);
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
