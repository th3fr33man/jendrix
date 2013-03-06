package com.seicom.jendrix;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.atomic.AtomicBoolean;

import android.util.Log;

// Class pour la récupération de l'échantillonnage audio et qui le stock dans un buffer

public class TcpServer extends Thread implements Runnable {

	private static final int TCP_SERVER_PORT = 1234;
	private ServerSocket ss;;// null;
	private Socket s;
	private BufferedReader in;

	private AtomicBoolean isThreadRunnning = new AtomicBoolean();
	private AtomicBoolean isThreadPausing = new AtomicBoolean();

	// Constructeur
	public TcpServer() {

		// TODO : Rajouter le BufferedReader objet Buffer

		setRunning(true);
		setPausing(false);

		Log.i("TcpServer", "startServeur");
		try {
			ss = new ServerSocket(TCP_SERVER_PORT);
		} catch (IOException e) {
			e.printStackTrace();
			Log.i("TcpServer", "serverThread");
		}
	}

	public void setPausing(boolean b) {
		isThreadPausing.set(b);
	}

	public boolean getPausing() {
		return isThreadPausing.get();
	}

	public void setRunning(boolean b) {
		isThreadRunnning.set(b);
	}

	public boolean getRunning() {
		return isThreadRunnning.get();
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		Log.i("TcpServer", "run");
		backGroundThreadProcessing();
	}
		

	private void backGroundThreadProcessing() {
		// Opération de récupération des echantillon
		try {
			s = ss.accept();
			String adIP = ss.getInetAddress().getHostAddress(); // retourne
																// l'@ip : A
																// revoir
			Log.i("TcpServer", adIP + " connected");
			in = new BufferedReader(new InputStreamReader(s.getInputStream()));
			go();
			//ss.close();
			Log.i("TcpServer", " fermeture connexion");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			Log.i("TcpServer", " erreur connexion");
		}
	}

	public void go() throws IOException {
		// try {
		// Thread.sleep(500);
		// } catch (InterruptedException ex) {
		// ex.printStackTrace();
		// Log.i("TcpServer", "erreur connexion2");
		// }
		startServer();
		Log.i("TcpServer", "go2");
		

		Log.i("TcpServer", "close socket");
	}

	public void startServer() throws IOException {
		int temp = 0;
		int temp1 = 0;
		int temp2 = 0;
		int etat = 0;
		// méthode pour lancer le serveur Tcp
		Log.i("TcpServer", "runTcpServer: ");
		try {
			Thread.sleep(1000);
			Log.i("TcpServer", "runTcpServer: sleep ");
			// boucle while, récupère en boucle les échantillons reçu par la
			// socket et les stock dans le buffer
			while (isThreadRunnning.get()) { // (!Thread.currentThread().isInterrupted()){

				if (isThreadPausing.get()) {
					Thread.sleep(2000);
					Log.i("tcpServer", "			en pause           ");
				} else {
					
					//Log.i("tcpServer", "			running           ");
					in.ready();
				
					// ////////////////////////////
					// pour l'échantillonnage 8bits
					// ////////////////////////////
					JendrixMainActivity.BUFFER[JendrixMainActivity.I] = (short)(in.read()<<8)/*-120*/;
					Log.i("TcpServer", ""+ JendrixMainActivity.BUFFER[JendrixMainActivity.I]);

					// case suivante du tableau
					JendrixMainActivity.I++;
					if (JendrixMainActivity.I == JendrixMainActivity.TAILLE_BUFFER) {
						JendrixMainActivity.I = 0;
						Log.i("TcpServer", "buffer a 1069 ");
					}

					

					// //////////////////////////////
					// pour l'échantillonnage 16 bits
					// //////////////////////////////
					// temp = in.read();
					// if (temp>>4==0) { //if ((temp&240)<240) {
					// temp1 = in.read();
					// temp2 = in.read();
					// } else {
					// temp1 = temp;
					// temp2 = in.read();
					// }
					//
					// //décallage de 8 bits
					// temp2 = temp2<<8;
					// JendrixMainActivity.BUFFER[JendrixMainActivity.I]=
					// (short)(temp1 + (temp2<<8));
					// Log.i("TcpServer",""+ temp1 + "et" + temp2);
					// Log.i("TcpServer",""+JendrixMainActivity.BUFFER[JendrixMainActivity.I]);

					// essai avec un switch TODO:A tester
					// temp = in.read();
					// if ((temp>>4)!=0) etat = 1;
					// else etat = 2;
					// switch (etat) {
					// case 1:
					// JendrixMainActivity.BUFFER[JendrixMainActivity.I]=
					// (short)(temp + (in.read()<<8));
					// break;
					// case 2:
					// JendrixMainActivity.BUFFER[JendrixMainActivity.I]=
					// (short)(in.read() + (in.read()<<8));
					// break;
					//
					// }
					
					
					// test réception d'une chaine sur le logcat
//					 String pass =in.readLine();
//					 Log.i("TcpServer",""+pass);
				}
			}

		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		// fin
	}
	
	public void closeSocket(){
		try {
			ss.close();
			s.close();
			Log.i("TcpServer", "close socket ");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
}
