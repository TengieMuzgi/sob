import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.util.EmptyStackException;
import org.junit.jupiter.api.Assertions;

public class ONPTests {
    private Stack<String> stack;
    private String singleTestElement = "Test element";
    private String[] testElements = new String[]{"Test element", "Test element2","Test element3","Test element4"};

    @Before
    public void prepare() {
        stack = new Stack<>();
    }

    @Test
    public void testEmptyStack() {
        assertTrue("Stack is not empty", stack.isEmpty());
    }

    @Test(expected = EmptyStackException.class)
    public void testPop() {
        stack.pop();
    }

    @Test(expected = EmptyStackException.class)
    public void testTop() {
        stack.top();
    }

    @Test(expected = EmptyStackException.class)
    public void testOperations() {
        stack.push(singleTestElement);
        assertEquals(singleTestElement,stack.top());
        assertEquals(singleTestElement,stack.top());
        assertEquals(singleTestElement,stack.top());
        assertEquals(singleTestElement,stack.top());
        assertFalse(stack.isEmpty());
        String value = stack.pop();
        assertSame("Objects are not same", singleTestElement, value);
        assertTrue(stack.isEmpty());
        stack.pop();
    }
    @Test(expected = EmptyStackException.class)
    public void testManyPushed() {
        String currentValue;
        for(String i : testElements) {
            stack.push(i);
        }
        for(int i=stack.size()-1; i>=0;i--) {
            assertEquals("Tested objects are not equal",testElements[i],stack.top());
            currentValue = stack.pop();
            assertSame("Objects are not same", testElements[i], currentValue);
        }
        assertTrue(stack.isEmpty());
        stack.pop();
    }

    @Test
    public void testNull() {
        stack.push(null);
        assertSame("Objects are not same", null, stack.pop());
    }

    @Test(expected = EmptyStackException.class)
    public void testAfterException() {
        stack.top();
        stack.push(singleTestElement);
        assertEquals(singleTestElement, stack.pop());
    }

    @Test
    public void additionTest() {
        assertEquals(5.0,Main.DoOperation(2.0,3.0,"+"), 0.001);
    }
    @Test
    public void substractionTest() {
        assertEquals(2.2,Main.DoOperation(4.5,2.3,"-"), 0.001);
    }
    @Test
    public void multiplicationTest() {
        assertEquals(42.32,Main.DoOperation(9.2,4.6,"*"), 0.001);
    }
    @Test
    public void divisionTest() {
        assertEquals(4.0,Main.DoOperation(8.0,2.0,"/"), 0.001);
    }
    @Test
    public void exponentiationTest() {
        assertEquals(27.0,Main.DoOperation(3.0,3.0,"^"), 0.001);
    }
    @Test
    public void squareRootTest() {
        assertEquals(3.0,Main.DoOperation(9.0,2.0,"p"), 0.001);
    }
    @Test
    public void moduloTest() {
        assertEquals(2.0,Main.DoOperation(5.0,3.0,"%"), 0.001);
    }

    @After
    public void clean() {
        stack = null;
    }
}
