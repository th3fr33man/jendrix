package Model;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;
import java.util.Enumeration;

import android.os.Handler;
import android.util.Log;
import android.widget.TextView;


public class Server implements Runnable {				//extends Activity 
	 
	    private TextView serverStatus;
	 
	    // default ip
	    public static String SERVERIP = "10.0.2.15";
	 
	    // designate a port
	    public static final int SERVERPORT = 8080;
	 
	    private Handler handler = new Handler();
	 
	    private ServerSocket serverSocket;
	 
//	    @Override
//	    protected void onCreate(Bundle savedInstanceState) {
//	        super.onCreate(savedInstanceState);
//	        setContentView(R.layout.server);
//	        serverStatus = (TextView) findViewById(R.id.server_status);
//	 
//	        SERVERIP = getLocalIpAddress();
//	 
//	        Thread fst = new Thread(new ServerThread());
//	        fst.start();
//	    }
	 
//	    public class ServerThread implements Runnable {
	 
	        public void run() {
	            try {
	                if (SERVERIP != null) {
	                    handler.post(new Runnable() {
	                        @Override
	                        public void run() {
	                            serverStatus.setText("Listening on IP: " + SERVERIP);
	                        }
	                    });
	                    serverSocket = new ServerSocket(SERVERPORT);
	                    while (true) {
	                        // listen for incoming clients
	                        Socket client = serverSocket.accept();
	                        handler.post(new Runnable() {
	                            @Override
	                            public void run() {
	                                serverStatus.setText("Connected.");
	                            }
	                        });
	 
	                        try {
	                            BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
	                            String line = null;
	                            while ((line = in.readLine()) != null) {
	                                Log.d("ServerActivity", line);
	                                handler.post(new Runnable() {
	                                    @Override
	                                    public void run() {
	                                        // do whatever you want to the front end
	                                        // this is where you can be creative
	                                    }
	                                });
	                            }
	                            break;
	                        } catch (Exception e) {
	                            handler.post(new Runnable() {
	                                @Override
	                                public void run() {
	                                    serverStatus.setText("Oops. Connection interrupted. Please reconnect your phones.");
	                                }
	                            });
	                            e.printStackTrace();
	                        }
	                    }
	                } else {
	                    handler.post(new Runnable() {
	                        @Override
	                        public void run() {
	                            serverStatus.setText("Couldn't detect internet connection.");
	                        }
	                    });
	                }
	            } catch (Exception e) {
	                handler.post(new Runnable() {
	                    @Override
	                    public void run() {
	                        serverStatus.setText("Error");
	                    }
	                });
	                e.printStackTrace();
	            }
	        }
//	    }
	 
	    // gets the ip address of your phone's network
	    private String getLocalIpAddress() {
	        try {
	            for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) {
	                NetworkInterface intf = en.nextElement();
	                for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
	                    InetAddress inetAddress = enumIpAddr.nextElement();
	                    if (!inetAddress.isLoopbackAddress()) { return inetAddress.getHostAddress().toString(); }
	                }
	            }
	        } catch (SocketException ex) {
	            Log.e("ServerActivity", ex.toString());
	        }
	        return null;
	    }
	 
//	    @Override
//	    protected void onStop() {
//	        super.onStop();
//	        try {
//	             // make sure you close the socket upon exiting
//	             serverSocket.close();
//	         } catch (IOException e) {
//	             e.printStackTrace();
//	         }
//	    }
	 
	}




























//import java.io.DataInputStream;
//import java.io.DataOutputStream;
//import java.io.IOException;
//import java.net.ServerSocket;
//import java.net.Socket;
//
//public class Server {
//
//	// public static void main(String[] args){
//
//	public Server() {
//		ServerSocket serverSocket = null;
//		Socket socket = null;
//		DataInputStream dataInputStream = null;
//		DataOutputStream dataOutputStream = null;
//
//		try {
//			serverSocket = new ServerSocket(1234);
//			System.out.println("Listening :1234");
//		} catch (IOException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//
//		while (true) {
//			try {
//				socket = serverSocket.accept();
//				dataInputStream = new DataInputStream(socket.getInputStream());
//				dataOutputStream = new DataOutputStream(
//						socket.getOutputStream());
//				System.out.println("ip: " + socket.getInetAddress());
//				System.out.println("message: " + dataInputStream.readUTF());
//				dataOutputStream.writeUTF("Hello!");
//			} catch (IOException e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			} finally {
//				if (socket != null) {
//					try {
//						socket.close();
//					} catch (IOException e) {
//						// TODO Auto-generated catch block
//						e.printStackTrace();
//					}
//				}
//
//				if (dataInputStream != null) {
//					try {
//						dataInputStream.close();
//					} catch (IOException e) {
//						// TODO Auto-generated catch block
//						e.printStackTrace();
//					}
//				}
//
//				if (dataOutputStream != null) {
//					try {
//						dataOutputStream.close();
//					} catch (IOException e) {
//						// TODO Auto-generated catch block
//						e.printStackTrace();
//					}
//				}
//			}
//		}
//	}
//}