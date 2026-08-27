import java.io.*;
import java.net.*;

public class Client {

    public static void main(String[] args) {

        try {
            Socket socket = new Socket("localhost", 5000);

            BufferedReader userInput = new BufferedReader(
                    new InputStreamReader(System.in));

            BufferedReader input = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));

            PrintWriter output = new PrintWriter(
                    socket.getOutputStream(), true);

            System.out.println("Connected to server.");
            System.out.println("Enter your message line by line.");
            System.out.println("Type 'Over' to terminate.");

            String message;

            while (true) {

                System.out.print("Enter: ");
                message = userInput.readLine();

                output.println(message);

                if (message.equalsIgnoreCase("Over")) {
                    break;
                }
            }

            // Receive timestamp from server
            String response = input.readLine();

            System.out.println("\nServer response:");
            System.out.println(response);

            socket.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}