package stevenphilley_addressbook;

import java.awt.BorderLayout;
import javax.swing.JPanel;
/**
 * A Container for the Contact data and the buttons.
 * 
 * @author    Steven Philley
 * @version   2014-12-06
 */
@SuppressWarnings("serial")
public class RightPane extends JPanel {
    
    ContactDataPane contactdatapane;
    ContactListPane contactlistpane;
    ButtonPane buttonpane;
    
    /**
     * RightPane requires an Address book of contacts so it can be passed 
     *      to the contact data pane.
     * 
     */
    RightPane(AddressBook addressbook, ContactListPane incontactlistpane)
    {
        this.setLayout(new BorderLayout());
        
        //Add the ContactDataPane and the ButtonPane
        contactlistpane = incontactlistpane;
        contactdatapane = new ContactDataPane(addressbook);
        buttonpane = new ButtonPane(contactdatapane, addressbook, contactlistpane);
        
        this.add(contactdatapane, BorderLayout.NORTH);
        this.add(buttonpane, BorderLayout.SOUTH);
        
    }
    
    public ContactDataPane getContactDataPane()
    {
        return contactdatapane;
    }
    
    public ContactListPane getContactListPane()
    {
        return contactlistpane;
    }
}
