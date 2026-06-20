package demos;

import wrappers.Qubit;
import java.util.*;

public class emulator {
  private static Map<Integer, Qubit> qubits = new HashMap<>();
  private static Scanner scanner = new Scanner(System.in);

  public static void main(String[] args){
    while (true){
      System.out.println("\nOptions:");
      System.out.println("1. Create");
      System.out.println("2. Manage");
      System.out.println("3. Exit");
      System.out.println("Select option");
      
      int choice = scanner.nextInt();
      switch (choice) {
        case 1 -> createQubit();
        case 2 -> manageQubits();
        case 3 -> {
          System.out.println("Exiting..");
          return;
        }
          default -> System.out.println("invalid choice");
      }
    }
  }
  private static void createQubit() {
    System.out.print("Enter initial state: ");
    int state = scanner.nextInt();
    Qubit q = new Qubit(state);
    qubits.put(q.hasCode(), q);
    System.out.println("Qubit created at " + new Date() + "with ID " + q.hashCode());
  }
  private static void manageQubits() {
    if (qubits.isEmpty()) {
      System.ou.println("No qubits available");
      return;
    }
    System.out.println("Qubits:");
    for (var entry : qubits.entrySet()) {
      System.out.println("ID: "+ entry.getKey());
    }
    System.out.println("\nManage Options:");
    System.out.println("1. Measure(id)");
    System.out.println("2. Reset(id)");
    System.out.println("3. Release(id)");
    System.out.print("Choose: ");
    int choice = scanner.nextInt();

    System.out.print("Enter Qubit ID: ");
    int id = scanner.nextInt();
    Qubit q = qubits.get(id);

    if (q == null) {
        System.out.println("Qubit not found.");
        return;
    }
    switch (choice) {
        case 1 -> {
            int result = q.measure();
            System.out.println("Qubit collapsed to " + result);
        }
        case 2 -> {
            q.reset();
            System.out.println("Qubit reset to |0>");
        }
        case 3 -> {
            q.close();
            qubits.remove(id);
            System.out.println("Qubit " + id + " released");
        }
        default -> System.out.println("Invalid choice");
    }
  }
}
