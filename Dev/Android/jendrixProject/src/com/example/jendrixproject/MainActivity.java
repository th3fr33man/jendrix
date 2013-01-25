package com.example.jendrixproject;
import Model.Server;
import android.app.Activity;
import android.os.Bundle;
import android.text.InputType;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends Activity implements View.OnClickListener {

private Button tb1=null;
private Server ecoute;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		EditText editText = new EditText(this);
		editText.setHint(R.string.editText);
		editText.setInputType(InputType.TYPE_TEXT_FLAG_MULTI_LINE);
		editText.setLines(5);
		
		/* méthode à comprendre sert à La référence  des boutons */
		setContentView(R.layout.activity_main);
	    tb1=(Button)findViewById(R.id.tb1);
		tb1.setOnClickListener(this);

		
	}
	
	
	public void onClick(View v) {
		  // On récupère l'identifiant de la vue, et en fonction de cet identifiant…
		  switch(v.getId()) {
		 
		    // Si l'identifiant de la vue est celui du premier bouton
		    case R.id.tb1:
		    /* Agir pour bouton 1 */
		    Toast.makeText(this, "Lancement de l'écoute", Toast.LENGTH_SHORT).show();
			ecoute = new Server();
			ecoute.run();
		    break;
		 
		    
		    // Si l'identifiant de la vue est celui du deuxième bouton     
//		    case R.id.tb2:
		    /* Agir pour bouton 2 */
//		    Toast.makeText(this, "Lancement de l'enregistrement", Toast.LENGTH_LONG).show();
//		    break;
		   
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
