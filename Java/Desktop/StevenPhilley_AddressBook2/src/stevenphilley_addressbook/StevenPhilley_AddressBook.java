package stevenphilley_addressbook;

import java.awt.BorderLayout;
import java.awt.Dimension;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.WindowConstants;

/**
 * Create the main JFrame
 * 
 * @author    Steven Philley
 * @version   2014-12-06
 */
public class StevenPhilley_AddressBook implements Runnable {

    private final AddressBook addressbook;
       
    public StevenPhilley_AddressBook()
    {
        //Create 'the' AddressBook.
        addressbook = new AddressBook();
    }
    
    /**
     * Create a new instance of self and add it to the event dispatch thread
     * 
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        //Build self which is a JFrame
        StevenPhilley_AddressBook mainjframe = new StevenPhilley_AddressBook();

        // schedule the run method to be on the event dispatch thread
        SwingUtilities.invokeLater(mainjframe);
    }

    /**
     * Creates the main JFrame and other panels.
     *  
     */
    @Override
    public void run() {

        // Build the JFrame
        JFrame frame = new JFrame("Steven Philley Address Book");
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setPreferredSize(new Dimension(600, 500));
        frame.pack();
        frame.setVisible(true);

        //Create a scroll pane that we can add the list of names to.
        ContactListPane contactlistpane = new ContactListPane(addressbook);
        contactlistpane.getScrollPane().setPreferredSize(new Dimension(200,300));
        //Create the right panel and pass along the addressbook, scroolpane list.
        
        RightPane rightpanel = new RightPane(addressbook, contactlistpane);
        
        contactlistpane.setContactDataPane(rightpanel.getContactDataPane());
        contactlistpane.getNamesList().setSelectedIndex(0);
        
        rightpanel.getContactListPane();
        
        // add components to the JFrame
        frame.add(contactlistpane.getScrollPane(), BorderLayout.WEST);
        frame.add(rightpanel, BorderLayout.EAST);
    }
}