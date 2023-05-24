import java.util.Scanner;

import static org.junit.Assert.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class Main {

    public static double DoOperation(double firstval, double secondval, String operator) throws ArithmeticException {
        double res = 0;
        switch (operator) {
            case "+": {
                res = firstval + secondval;
            }
            break;
            case "-": {
                res = firstval - secondval;
            }
            break;
            case "*": {
                res = firstval * secondval;
            }
            break;
            case "/": {
                if(secondval == 0) {
                    throw new ArithmeticException("Division by 0 detected.");
                }
                res = (double) (firstval / secondval);
            }
            break;
            case "^": {
                res = Math.pow(firstval, secondval);
            }
            break;
            case "p": {
                res = Math.pow(firstval, 1 / secondval);
            }
            break;
            case "%": {
                res = firstval % secondval;
            }
            break;
            default: System.out.println("Incorrect operator");
        }
        return res;
    }

    public static void main(String[] args) {
        Stack<Double> values = new Stack();
        String equation;
        System.out.println("Insert equation in Reverse Polish Notation: \n");
        Scanner input = new Scanner(System.in);
        equation = input.nextLine();
        String[] operands = equation.split(" ");
        for (String operand : operands) {
            try {
                values.push(Double.parseDouble(operand));
            } catch (NumberFormatException except) {
                double value2 = values.top();
                values.pop();
                double value1 = values.top();
                values.pop();
                double w = DoOperation(value1, value2, operand);
                values.push(w);
            }
        }
        System.out.println("Result: " + values.top());
    }
}