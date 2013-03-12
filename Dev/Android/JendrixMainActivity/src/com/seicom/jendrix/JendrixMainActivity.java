package com.seicom.jendrix;

import java.util.concurrent.atomic.AtomicBoolean;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.ToggleButton;

public class JendrixMainActivity extends Activity {

	private TcpServer tcpServer;
	private AudioServer audioServer;
	public static volatile short[] BUFFER;
	public static volatile int I = 0;
	public static final int TAILLE_BUFFER = 2200;
	public static volatile int COUNT = 0;
	private Handler handler;

	// Button ecoute;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_jendrix_main);

		ToggleButton ecoute = (ToggleButton) findViewById(R.id.onoff);

		handler = new Handler() {
			/*
			 * (non-Javadoc)
			 * 
			 * @see android.os.Handler#handleMessage(android.os.Message)
			 */
			@Override
			public void handleMessage(Message msg) {
				super.handleMessage(msg);
				Log.i("test handler", "handle message called ");
				// be sure the handler is running before doing something
				if (tcpServer.getRunning()) {
					Log.i("test handler",
							"handle message calls updateProgress ");
				}
			}
		};

		ecoute.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(CompoundButton buttonView,
					boolean isChecked) {
				if (isChecked) {
					//tcpServer.setPausing(false);
					I=0;
					if (audioServer.getRunning()==false) {
						audioServer.setRunning(true);
						audioServer.setPausing(false);
						audioServer.start();
					} else {
						audioServer.setPausing(false);
					}
				} else
					audioServer.setPausing(true);
					//tcpServer.setPausing(true);
			}

			// TODO : a voir pour implémenter un type booleen qui serait dans
			// les while des thread pour les arrêter
			// Utiliser la classe Handler pour communiquer des thread vers
			// l'activity principale
			// si la méthode interrupt ne fonctionne pas voir pour en utiliser
			// une autre

		});

		BUFFER = new short[TAILLE_BUFFER];
		tcpServer = new TcpServer();
		audioServer = new AudioServer();
		Log.i("TcpServer", "onCreate:activity ");
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_jendrix_main, menu);
		return true;
	}

	protected void onStart() {
		super.onStart();
		tcpServer.start();
		tcpServer.setRunning(true);
		Log.i("TcpServer", "onStart:socket ");
	}

	@Override
	protected void onRestart() {
		super.onRestart();
		Log.i("TcpServer", "onRestart: ");
		tcpServer.setRunning(true);
	}

	@Override
	public void onResume() {
		super.onResume(); // Always call the superclass method first
		Log.i("TcpServer", "onResume: ");
		tcpServer.setPausing(false);
		audioServer.setPausing(false);
	}

	@Override
	public void onPause() {
		super.onPause(); // Always call the superclass method first
		Log.i("TcpServer", "onPause: ");
		audioServer.setPausing(true);
		tcpServer.setPausing(true);
	}

	@Override
	protected void onStop() {
		super.onStop();
		Log.i("TcpServer", "onStop: ");
		tcpServer.setRunning(false);
		tcpServer.closeSocket();
		audioServer.setRunning(false);
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
		Log.i("TcpServer", "onDestroy: ");
		tcpServer.setRunning(false);
		audioServer.setRunning(false);
	}

}
