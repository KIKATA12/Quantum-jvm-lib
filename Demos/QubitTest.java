package demos;

import java.util.Scanner;
import wrappers.Qubit;

public class QubitTest {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    try (Qubit q = new Qubit()) {
        System.out.println("=== Qubit Interactive Demo ===");
        System.out.println("Choose an operation: create, initialize, measure, reset, free");
        System.out.print("> ");
        String choice = scanner.next();
    
        switch (choice) {
            case "create":
                System.out.println("Qubit created.");
                break;
    
            case "initialize":
                System.out.print("Enter state (0 or 1): ");
                int state = scanner.nextInt();
                q.initialize(state);
                System.out.println("Qubit initialized to state " + state);
                break;
    
            case "measure":
                int result = q.measure();
                System.out.println("Measurement result: " + result);
                break;
    
            case "reset":
                q.reset();
                System.out.println("Qubit reset.");
                break;
    
            case "free":
                System.out.println("Qubit freed automatically at close.");
                break;
    
            default:
                System.out.println("Unknown operation: " + choice);
        }
    } catch (Exception e) {
        e.printStackTrace();
    }
    
    scanner.close();
    }
}
