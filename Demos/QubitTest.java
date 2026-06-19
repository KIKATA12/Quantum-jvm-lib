package demos;

import wrappers.Qubit;

public class QubitTest {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    if (args.length == 0){
      System.out.println("Usage: java demos.QubitTest <create|initialize|measure|reset|free> [state}");  
      return;
    }    
    try (Qubit q = new Qubit()) {
      switch (args[0]) {
          case "create":
              System.out.println("Qubit created.");
              break;
          case "initialize":
              int state = args.length > 1 ? Integer.parseInt(args[1]) : 0;
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
    }
  }
}
