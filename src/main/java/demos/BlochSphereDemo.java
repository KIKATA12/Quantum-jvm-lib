package demos;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import wrappers.BlochSphere;

public class BlochSphereDemo {
  private static final class ParsedState {
    final double alphaReal;
    final double alphaImag;
    final double betaReal;
    final double betaImag;

    ParsedState(double alphaReal, double alphaImag, double betaReal, double betaImag) {
      this.alphaReal = alphaReal;
      this.alphaImag = alphaImag;
      this.betaReal = betaReal;
      this.betaImag = betaImag;
    }
  }

  private static final class Token {
    final String value;
    final String type;

    Token(String value, String type) {
      this.value = value;
      this.type = type;
    }
  }

  private static final class Tokenizer {
    private final String input;
    private final List<Token> tokens = new ArrayList<>();
    private int index;

    Tokenizer(String input) {
      this.input = input;
    }

    List<Token> tokenize() {
      while (index < input.length()) {
        char current = input.charAt(index);
        if (Character.isWhitespace(current)) {
          index++;
          continue;
        }

        if (current == '+' || current == '-' || current == '*' || current == '/' || current == '(' || current == ')') {
          tokens.add(new Token(String.valueOf(current), "SYMBOL"));
          index++;
          continue;
        }

        if (current == '|') {
          if (index + 2 < input.length() && input.charAt(index + 2) == '>') {
            char basis = input.charAt(index + 1);
            if (basis == '0') {
              tokens.add(new Token("|0>", "BASIS"));
            } else if (basis == '1') {
              tokens.add(new Token("|1>", "BASIS"));
            } else {
              throw new IllegalArgumentException("Unsupported basis state near: " + input.substring(index));
            }
            index += 3;
            continue;
          }
        }

        if (Character.isDigit(current) || current == '.') {
          int start = index;
          while (index < input.length() && (Character.isDigit(input.charAt(index)) || input.charAt(index) == '.')) {
            index++;
          }
          tokens.add(new Token(input.substring(start, index), "NUMBER"));
          continue;
        }

        if (Character.isLetter(current)) {
          int start = index;
          while (index < input.length() && Character.isLetter(input.charAt(index))) {
            index++;
          }
          tokens.add(new Token(input.substring(start, index), "IDENTIFIER"));
          continue;
        }

        throw new IllegalArgumentException("Unsupported character '" + current + "' in input");
      }

      tokens.add(new Token("EOF", "EOF"));
      return tokens;
    }
  }

  private static final class Parser {
    private final List<Token> tokens;
    private int index;

    Parser(List<Token> tokens) {
      this.tokens = tokens;
    }

    ParsedState parse() {
      double alphaReal = 0.0;
      double alphaImag = 0.0;
      double betaReal = 0.0;
      double betaImag = 0.0;

      while (!peek("EOF")) {
        double sign = 1.0;
        if (peek("SYMBOL", "+")) {
          consume();
        } else if (peek("SYMBOL", "-")) {
          sign = -1.0;
          consume();
        }

        double coefficient = 1.0;
        if (!peek("BASIS")) {
          coefficient = parseExpression();
        }
        coefficient *= sign;

        if (!peek("BASIS")) {
          throw new IllegalArgumentException("Expected a basis state like |0> or |1>");
        }

        String basis = consume().value;
        if ("|0>".equals(basis)) {
          alphaReal += coefficient;
        } else if ("|1>".equals(basis)) {
          betaReal += coefficient;
        }
      }

      return new ParsedState(alphaReal, alphaImag, betaReal, betaImag);
    }

    private double parseExpression() {
      double value = parseTerm();
      while (peek("SYMBOL", "+") || peek("SYMBOL", "-")) {
        String op = consume().value;
        double rhs = parseTerm();
        value = "+".equals(op) ? value + rhs : value - rhs;
      }
      return value;
    }

    private double parseTerm() {
      double value = parseUnary();
      while (peek("SYMBOL", "*") || peek("SYMBOL", "/")) {
        String op = consume().value;
        double rhs = parseUnary();
        value = "*".equals(op) ? value * rhs : value / rhs;
      }
      return value;
    }

    private double parseUnary() {
      if (peek("SYMBOL", "+")) {
        consume();
        return parseUnary();
      }
      if (peek("SYMBOL", "-")) {
        consume();
        return -parseUnary();
      }
      return parsePrimary();
    }

    private double parsePrimary() {
      Token token = peekToken();
      if ("NUMBER".equals(token.type)) {
        consume();
        return Double.parseDouble(token.value);
      }
      if (peek("SYMBOL", "(")) {
        consume();
        double value = parseExpression();
        if (!peek("SYMBOL", ")")) {
          throw new IllegalArgumentException("Missing closing parenthesis");
        }
        consume();
        return value;
      }
      if (peek("IDENTIFIER")) {
        String identifier = consume().value;
        if ("sqrt".equalsIgnoreCase(identifier)) {
          return Math.sqrt(parseUnary());
        }
        if ("pi".equalsIgnoreCase(identifier)) {
          return Math.PI;
        }
        if ("e".equalsIgnoreCase(identifier)) {
          return Math.E;
        }
      }
      throw new IllegalArgumentException("Unexpected token: " + token.value);
    }

    private boolean peek(String type) {
      return peek(type, null);
    }

    private boolean peek(String type, String value) {
      Token token = peekToken();
      return token.type.equals(type) && (value == null || value.equals(token.value));
    }

    private Token peekToken() {
      if (index >= tokens.size()) {
        return tokens.get(tokens.size() - 1);
      }
      return tokens.get(index);
    }

    private Token consume() {
      Token token = peekToken();
      index++;
      return token;
    }
  }

  public static void main(String[] args) {
    String input = args.length > 0 ? String.join(" ", args) : promptForInput();
    ParsedState state = parseState(input);

    try (BlochSphere sphere = new BlochSphere()) {
      double[] angles = sphere.computeAngles(state.alphaReal, state.alphaImag, state.betaReal, state.betaImag);
      double[] vector = sphere.computeVector(state.alphaReal, state.alphaImag, state.betaReal, state.betaImag);
      double[] densityMatrix = sphere.computeDensityMatrix(state.alphaReal, state.alphaImag, state.betaReal, state.betaImag);

      System.out.println("Input state: " + input);
      System.out.println("Alpha: " + formatComplex(state.alphaReal, state.alphaImag));
      System.out.println("Beta: " + formatComplex(state.betaReal, state.betaImag));
      System.out.println("Density matrix:");
      printDensityMatrix(densityMatrix);
      System.out.println("theta = " + angles[0]);
      System.out.println("azimuthal = " + angles[1]);
      System.out.println("x = " + angles[2]);
      System.out.println("y = " + angles[3]);
      System.out.println("z = " + angles[4]);
      System.out.println("Bloch vector: (" + vector[0] + ", " + vector[1] + ", " + vector[2] + ")");
    }
  }

  private static ParsedState parseState(String input) {
    String trimmed = input == null ? "" : input.trim();
    if (trimmed.isEmpty()) {
      throw new IllegalArgumentException("Please provide a qubit state such as 1/2 |0> + (sqrt 3)/2 |1>");
    }

    Tokenizer tokenizer = new Tokenizer(trimmed);
    Parser parser = new Parser(tokenizer.tokenize());
    return parser.parse();
  }

  private static String promptForInput() {
    System.out.println("Enter a qubit state such as: 1/2 |0> + (sqrt 3)/2 |1>");
    try {
      BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
      String line = reader.readLine();
      return line == null || line.trim().isEmpty() ? "1/2 |0> + (sqrt 3)/2 |1>" : line;
    } catch (IOException ex) {
      return "1/2 |0> + (sqrt 3)/2 |1>";
    }
  }

  private static String formatComplex(double real, double imag) {
    if (Math.abs(imag) < 1e-12) {
      return Double.toString(real);
    }
    return real + " + " + imag + "i";
  }

  private static void printDensityMatrix(double[] densityMatrix) {
    double rho00Real = densityMatrix[0];
    double rho00Imag = densityMatrix[1];
    double rho01Real = densityMatrix[2];
    double rho01Imag = densityMatrix[3];
    double rho10Real = densityMatrix[4];
    double rho10Imag = densityMatrix[5];
    double rho11Real = densityMatrix[6];
    double rho11Imag = densityMatrix[7];

    System.out.println("[[" + formatComplex(rho00Real, rho00Imag) + ", " + formatComplex(rho01Real, rho01Imag) + "],");
    System.out.println(" [" + formatComplex(rho10Real, rho10Imag) + ", " + formatComplex(rho11Real, rho11Imag) + "]] ");
  }
}
