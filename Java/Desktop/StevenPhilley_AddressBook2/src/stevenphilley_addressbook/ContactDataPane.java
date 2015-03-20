package stevenphilley_addressbook;

import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.TreeMap;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

/**
 * Pane to display all the contact data.
 * 
 * @author    Steven Philley
 * @version   2014-12-06
 */
@SuppressWarnings("serial")
public class ContactDataPane extends JPanel {
    
    private final TreeMap<String, JComponent> fieldcomponents;
    private final ArrayList<String> fieldnames;
    private final AddressBook addressbook;
    
    /**
     * Add the text boxes and labels to the ContactDataPane
     * 
     * @param ab - the address book in the application.
     */
    public ContactDataPane(AddressBook ab)
    {
        addressbook = ab;
        
        fieldnames = addressbook.getFields();
        
        this.setLayout(new GridLayout(0,2));
        
        fieldcomponents = new TreeMap<>();
        
        //Creates all the text boxes and labels
        createDefaultComponents();
        
        //Adds the labels and text boxes to this panel.
        addComponentsToPanel();
        
        //populate the text boxes with the first record.
        populateTextBoxesWithRecord("");
    } 
    
    /**
     * Clears the text boxes.
     * 
     */
    public void clearTextBoxes()
    {
        for(String s : fieldnames)
        {
            JTextField temptextfield = (JTextField)fieldcomponents.get(s+"TextBox");
            
            temptextfield.setText("");
        }
    }
    /**
     * Updates a specific contact in the address book using the values in the text boxes.
     * 
     * 
     */
    public void updateContactFromTextFields()
    {
        ContactData contact = new ContactData();
                
        //loops through the available fiels and grab the value from the text box
        for(String s : fieldnames)
        {
            JTextField temptextfield = (JTextField)fieldcomponents.get(s+"TextBox");
            
            contact.setValue(s, temptextfield.getText());
        }
        
        if(!contact.getValue("First Name").isEmpty() || !contact.getValue("Last Name").isEmpty())
        {
            if(!addressbook.updateContact(contact))
            {
                JOptionPane.showMessageDialog(SwingUtilities.getRoot(this), 
                        "You already have a record for " 
                        + contact.getValue("First Name") + " " + contact.getValue("Last Name"));
            }
        }
        else
        {
            JOptionPane.showMessageDialog(SwingUtilities.getRoot(this), 
                    "You must provide either a First or Last Name" );
        }
    }
    
    /**
     * Adds a contact to the address book using the values in the text boxes.
     * 
     * 
     */
    public void addContactFromTextFields()
    {
        ContactData contact = new ContactData();
                
        //loops through the available fiels and grab the value from the text box
        for(String s : fieldnames)
        {
            JTextField temptextfield = (JTextField)fieldcomponents.get(s+"TextBox");
            
            contact.setValue(s, temptextfield.getText());
        }
        
        if(!contact.getValue("First Name").isEmpty() || !contact.getValue("Last Name").isEmpty())
        {
            if(!addressbook.addContact(contact))

            {
                JOptionPane.showMessageDialog(SwingUtilities.getRoot(this), "You already have a record for " 
                        + contact.getValue("First Name") + " " + contact.getValue("Last Name"));
            }
        }
        else
        {
            JOptionPane.showMessageDialog(SwingUtilities.getRoot(this), "You must provide either a First or Last Name" );
        }
    }
          
    /**
     * populates the text boxes with a specific record.
     * 
     * @param key
     */
    public void populateTextBoxesWithRecord(String key)
    {
        //For each field lets populate the Text Boxes.
        for(String s : fieldnames)
        {
            JTextField temptextfield = (JTextField)fieldcomponents.get(s+"TextBox");

            // by default getContact will just grab the first record is the key is empty.
            
            try{
                temptextfield.setText(addressbook.getContact(key).getValue(s));
            }
            catch (NullPointerException e)
            {
                System.out.println("WARNING: There is no default row.");
                
                //break out of the for loop
                break;
            }
        }
    }
    
    /**
     * Create labels and text fields
     * 
     */
    private void createDefaultComponents()
    {
        for(String currentfieldname : fieldnames)
        {
            JLabel tempJLabel = new JLabel(currentfieldname);
            JTextField tempJTextField = new JTextField(currentfieldname);
            tempJTextField.setName(currentfieldname);
            tempJTextField.getDocument().addDocumentListener(new DocumentListener() {

                @Override
                public void insertUpdate(DocumentEvent e) {
                    showUpdateButton("insert");
                }

                @Override
                public void removeUpdate(DocumentEvent e) {
                    showUpdateButton("remove");
                }

                @Override
                public void changedUpdate(DocumentEvent e) {
                    showUpdateButton("change");
                }
                
                });
            
            
            //Add the JLabel and JTextField
            fieldcomponents.put(currentfieldname + "Label", tempJLabel);
            fieldcomponents.put(currentfieldname + "TextBox", tempJTextField);
        }
    }
    
    /**
     * Show the save button when doing an update to a text field.
     */
    private void showUpdateButton(String type)
    {
        System.out.println(type);
    }
    
    
    /**
     * Add the labels and textfields to this panel
     * 
     */
    private void addComponentsToPanel()
    {     
        //Loops through the field names and grab the corissponding component,
        //  then add them to the panel.
        for(String s : fieldnames)
        {
            JLabel templabel = (JLabel)fieldcomponents.get(s+"Label");
            JTextField temptextfield = (JTextField)fieldcomponents.get(s+"TextBox");
            
            templabel.setHorizontalAlignment(JLabel.RIGHT);
            temptextfield.setPreferredSize(new Dimension(200,30));
            
            this.add(templabel);
            this.add(temptextfield);
        }
    }
}
