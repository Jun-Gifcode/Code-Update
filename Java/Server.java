import java.io.*;
import java.net.*;
import java.time.LocalDateTime;

public class Server {

    public static void main(String[] args) {

        try {
            ServerSocket serverSocket = new ServerSocket(5000);

            System.out.println("Server started.");
            System.out.println("Waiting for client...");

            Socket socket = serverSocket.accept();

            System.out.println("Client connected.");

            BufferedReader input = new BufferedReader(
                    new InputStreamReader(socket.getInputStream()));

            PrintWriter output = new PrintWriter(
                    socket.getOutputStream(), true);

            String message;

            while ((message = input.readLine()) != null) {

                if (message.equalsIgnoreCase("Over")) {
                    break;
                }

                // Convert client's input to uppercase
                String modifiedMessage = message.toUpperCase();

                // Display modified message at server
                System.out.println("Received: " + modifiedMessage);
            }

            // Send timestamp to client
            String timestamp = LocalDateTime.now().toString();
            output.println("Program terminated at: " + timestamp);

            socket.close();
            serverSocket.close();

            System.out.println("Server terminated.");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}