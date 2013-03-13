package com.seicom.jendrix;

import java.util.concurrent.atomic.AtomicBoolean;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.util.Log;

public class AudioServer extends Thread implements Runnable {

	private TcpServer tcpServer;
	private AudioTrack aT;
	private AtomicBoolean isThreadRunnning = new AtomicBoolean(false);
	private AtomicBoolean isThreadPausing = new AtomicBoolean(false);

	// constructeur
	public AudioServer(TcpServer TcpS) {
		// préparation du hardware pour la lecture audio
		tcpServer=TcpS;
		aT = new AudioTrack(AudioManager.STREAM_MUSIC, 11520,
				AudioFormat.CHANNEL_OUT_MONO, AudioFormat.ENCODING_PCM_16BIT,
				AudioTrack.getMinBufferSize(11520,
						AudioFormat.CHANNEL_OUT_MONO,
						AudioFormat.ENCODING_PCM_16BIT), AudioTrack.MODE_STREAM);
	}

	public AudioServer() {
		// préparation du hardware pour la lecture audio
		aT = new AudioTrack(AudioManager.STREAM_MUSIC, 11520,
				AudioFormat.CHANNEL_OUT_MONO, AudioFormat.ENCODING_PCM_16BIT,
				AudioTrack.getMinBufferSize(11520,
						AudioFormat.CHANNEL_OUT_MONO,
						AudioFormat.ENCODING_PCM_16BIT), AudioTrack.MODE_STREAM);
	}
	
	
	// TODO Créer une interface pour implémenter les méthodes communes au 2 Thread
	// ou voir pour une autre méthode de contrôl
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
		Log.i("AudioServer", "run");
		doInBackGroundThread();
		aT.stop();
	}

	private void doInBackGroundThread() {
		int i = 0;

		// try {
		// Thread.sleep(200);
		// } catch (InterruptedException ex) {
		// ex.printStackTrace();
		// Log.i("AudioServer", "go");
		// }
		int buf=AudioTrack.getMinBufferSize(11520,
				AudioFormat.CHANNEL_OUT_MONO,
				AudioFormat.ENCODING_PCM_16BIT);
		Log.i("AudioServer", "lecture de la musique, BUFFER "+ buf);

		try {
			Thread.sleep(1);
			while (isThreadRunnning.get()) {
				 aT.setLoopPoints(0,JendrixMainActivity.BUFFER.length/4,-1);
				// //pour la lecture en boucle, ne fonctionne pas
				if (isThreadPausing.get()) {
					aT.pause();
					aT.flush();
					Thread.sleep(2000); // (!Thread.currentThread().isInterrupted()){
										// // essai pour l'utilisation des
										// interrupt pour stopper proporement le
										// thread -> while
										// (!this.isInterrupted()){
					Log.i("AudioServer", "			en pause           ");
				} else {
					if (aT.getPlayState()!=3) aT.play();
					/*if (JendrixMainActivity.I<50){
						Thread.sleep(10);
					} else*/ 	i = aT.write(JendrixMainActivity.BUFFER, 0,
							JendrixMainActivity.TAILLE_BUFFER);
					Log.i("AudioServer", "           " + i); // retourne le
																// nombre de
																// byte lu
					
				}

			}

		} catch (Throwable t) {
			// just end the background thread

		}

	}

	// private int calculI(){
	// int i=0;
	//
	// if (JendrixMainActivity.I>1000) i= JendrixMainActivity.I-1000;
	// else if (JendrixMainActivity.I<=1000) {
	// i=JendrixMainActivity.TAILLE_BUFFER-1000+JendrixMainActivity.I;
	// }
	// return i;
	// }
	//
	// public void run() {
	// // TODO Auto-generated method stub
	//
	// // lancement de la lecture
	// Log.i("TcpServer", "reception audio en cour ");
	// for (int i=0; i<TcpServer.TAILLE_BUFFER; i++){
	// aT.write(TcpServer.BUFFER, i, TcpServer.TAILLE_BUFFER);
	// if (i==TcpServer.TAILLE_BUFFER) i=0;
	// }
	// }

}
