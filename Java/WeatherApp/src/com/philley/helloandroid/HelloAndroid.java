package com.philley.helloandroid;

import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.StringReader;
import java.net.HttpURLConnection;
import java.net.URL;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class HelloAndroid extends Activity {
    /** Called when the activity is first created. */
	
	private String readStream(InputStream is) {
	    try {
	      ByteArrayOutputStream bo = new ByteArrayOutputStream();
	      int i = is.read();
	      while(i != -1) {
	        bo.write(i);
	        i = is.read();
	      }
	      return bo.toString();
	    } catch (IOException e) {
	      return "";
	    }
	}
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        final Button button1 = (Button) findViewById(R.id.button1);
        final EditText editText1 = (EditText) findViewById(R.id.editText1);
       
        final EditText zipInput = (EditText) findViewById(R.id.zipInput);
        
       
        
        
        button1.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
            	
            	setContentView(R.layout.weather);
            	final TextView zipView = (TextView) findViewById(R.id.zipView);
            	
            	zipView.setText(zipInput.getText());
            	
            	String myStringStream = null;
            	
            	try {
            		
            		InputStream in = null;
            		URL url = new URL("http://www.google.com/ig/api?weather=" + zipInput.getText());
            	   HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
            	   try {
            	     in = new BufferedInputStream(urlConnection.getInputStream());
            	     myStringStream = readStream(in);
            	   }
            	   finally {
              	     urlConnection.disconnect();
              	   }
            	 
	            	if (in != null)
	            	{
	            		//zipView.setText(myStringStream);
	            	}
	            	else
	            	{
	            		zipView.setText("Nothing!");
	            	}
	            	
	            	DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
	            	DocumentBuilder dBuilder = null;
					try {
						dBuilder = dbFactory.newDocumentBuilder();
					} catch (ParserConfigurationException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
	            	Document doc = null;
					try {
						InputSource is = new InputSource(new StringReader(myStringStream));
						doc = dBuilder.parse(is);
						String myString = "Hello";
					} catch (SAXException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
	            	doc.getDocumentElement().normalize();
	            	
	            	zipView.setText(doc.getElementsByTagName("temp_f").item(0).getAttributes().getNamedItem("data").getNodeValue());
            	   
            	}
            	catch(Exception e){ zipView.setText(e.toString()); }
            }
        });
    }
}

