package com.example.jendrixproject;
import android.view.View;
//N'oubliez pas de déclarer le bon package dans lequel se trouve le fichier !

import android.app.Activity;
import android.os.Bundle;
import android.text.InputType;
import android.widget.Button;
import android.widget.EditText;
//import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity implements View.OnClickListener {
//	private TextView coucou = null;
//	private String hello;
private Button b1=null, b2=null;
	
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		EditText editText = new EditText(this);
		editText.setHint(R.string.editText);
		editText.setInputType(InputType.TYPE_TEXT_FLAG_MULTI_LINE);
		editText.setLines(5);
		
		/* méthode à comprendre sert à La référence  des boutons */

		setContentView(R.layout.activity_main);
		
	    b1=(Button)findViewById(R.id.b1);
	    b2=(Button)findViewById(R.id.b2);
		
//		Button b1 = new Button(this);
//		Button b2 = new Button(this);

		b1.setOnClickListener(this);
		b2.setOnClickListener(this);
		

		
//		hello = getResources().getString(R.string.hello_world);
//		hello = hello.replaceAll("world", "seicom");
//		coucou = new TextView(this);
//		coucou.setText(hello);
//		setContentView(coucou);
		
	}
	
	
	public void onClick(View v) {
		  // On récupère l'identifiant de la vue, et en fonction de cet identifiant…
		  switch(v.getId()) {
		 
		    // Si l'identifiant de la vue est celui du premier bouton
		    case R.id.b1:
		    /* Agir pour bouton 1 */
		    Toast.makeText(this, "Lancement de l'écoute", Toast.LENGTH_SHORT).show();
		    break;
		 
		    // Si l'identifiant de la vue est celui du deuxième bouton     
		    case R.id.b2:
		    /* Agir pour bouton 2 */
		    Toast.makeText(this, "Lancement de l'enregistrement", Toast.LENGTH_LONG).show();
		    break;
		   
		    /* etc. */
		  }
		}

}

/*
 * code par défaut lors de la création du projet
 */
// import android.os.Bundle;
// import android.app.Activity;
// import android.view.Menu;
//
// public class MainActivity extends Activity {
//
// @Override
// protected void onCreate(Bundle savedInstanceState) {
// super.onCreate(savedInstanceState);
// setContentView(R.layout.activity_main);
// }
//
// @Override
// public boolean onCreateOptionsMenu(Menu menu) {
// // Inflate the menu; this adds items to the action bar if it is present.
// getMenuInflater().inflate(R.menu.activity_main, menu);
// return true;
// }
//
// }
