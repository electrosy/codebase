package stevenphilley_addressbook;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.UnsupportedEncodingException;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

/**
 * A panel to hold the buttons for contact data control.
 * 
 * @author    Steven Philley
 * @version   2014-12-06
 */
@SuppressWarnings("serial")
public class ButtonPane extends JPanel 
{
    
    private final JButton nextbutton;
    private final JButton previousbutton;
    private final JButton newbutton;
    private final JButton savebutton;
    private final JButton deletebutton;
    private final JButton updatebutton;
    private final JList list;
    private final ContactDataPane contactdatapane;
    private final ContactListPane contactlistpane;
    private final AddressBook addressbook;
    
    public ButtonPane(ContactDataPane inputcontactdatapane, AddressBook inaddressbook, ContactListPane inputcontactlistpane)
    {
        //assign the input values to this object
        contactdatapane = inputcontactdatapane;
        contactlistpane = inputcontactlistpane;
        addressbook = inaddressbook;
        
        //assign the input list to this list.
        list = contactlistpane.getNamesList();
        
        //Create buttons
        nextbutton = new JButton("Next");
        previousbutton = new JButton("Previous");
        newbutton = new JButton("New");
        savebutton = new JButton("Save");
        deletebutton = new JButton("Delete");
        updatebutton = new JButton("Update");
        
        //some buttons should start disabled.
        nextbutton.setEnabled(false);
        previousbutton.setEnabled(false);
        deletebutton.setEnabled(false);
        
        //Set sizes for buttons
        newbutton.setPreferredSize(new Dimension(75,26));
        savebutton.setPreferredSize(new Dimension(75,26));
        
        //disable prev and next if there is not more than one record.
        shouldEnablePrevAndNext();
        //disable delete if there is not at least one record.
        shouldEnableDelete();
        
        //Logic for the nextbutton click
        nextbutton.addActionListener(new ActionListener()
            {
                @Override
                public void actionPerformed(ActionEvent e) {
                    System.out.println("Next!");
                    switchToNext();
                }
            }
        );
        
        //Logic for the previousbutton click
        previousbutton.addActionListener(new ActionListener()
            {
                @Override
                public void actionPerformed(ActionEvent e) {
                    System.out.println("Previous!");
                    switchToPrevious();
                }
            }
        );
        
        //Logic for the newbutton click
        newbutton.addActionListener(new ActionListener()
            {
                @Override
                public void actionPerformed(ActionEvent e) {
                    System.out.println("New!");
                    
                    newbutton.setVisible(false);
                    savebutton.setVisible(true);
                    
                    contactdatapane.clearTextBoxes();
                    list.removeSelectionInterval(0, list.getModel().getSize());
                    
                    redrawParentFrame(); //Graphics bug fix. TODO - only needs to be called the first time the new button is clicked.
                }
            }
        );
        
        //Logic for the savebutton click
        savebutton.addActionListener(new ActionListener()
            {
                @Override
                public void actionPerformed(ActionEvent e) {
                    System.out.println("Save!");
                    
                    savebutton.setVisible(false);
                    newbutton.setVisible(true);
                    
                    contactdatapane.addContactFromTextFields();
                    contactlistpane.updateNamesList("");
                    
                    shouldEnablePrevAndNext();
                    shouldEnableDelete();
                    
                    //Save the addressbook data to file.
                    try {
                        addressbook.saveDataToFile();
                    } catch (UnsupportedEncodingException ex) {
                        System.out.println("ERROR: " + ex.getMessage());
                    }
                }
            }
        );
        
        //Logic for the deletebutton click
        deletebutton.addActionListener(new ActionListener()
            {
                @Override
                public void actionPerformed(ActionEvent e) 
                {
                    System.out.println("Clicked Delete");
                    
                    String teststring = contactlistpane.getNamesList().getSelectedValue().toString();
                    
                    //addressbook.removeContact();
                    contactlistpane.updateNamesList("delete");
                            
                    shouldEnablePrevAndNext();
                    shouldEnableDelete();
                    
                    //Get the first and last name which is the key and then populate the text boxes with that record.
                    String key = contactlistpane.getNamesList().getSelectedValue().toString();
                    contactdatapane.populateTextBoxesWithRecord(key);
                    
                    //Save the addressbook data to file.
                    try 
                    {
                        addressbook.saveDataToFile();
                    } 
                    catch (UnsupportedEncodingException ex)
                    {
                        System.out.println("ERROR: " + ex.getMessage());
                    }
                }
            }
        );
        
        //Logic for the updatebutton click
        updatebutton.addActionListener(new ActionListener()
            {
                @Override
                public void actionPerformed(ActionEvent e) 
                {
                    System.out.println("Clicked Update");                    
                    
                    contactdatapane.updateContactFromTextFields();
                    contactlistpane.updateNamesList("");
                            
                    shouldEnablePrevAndNext();
                    shouldEnableDelete();
                    
                    //Save the addressbook data to file.
                    try 
                    {
                        addressbook.saveDataToFile();
                    } 
                    catch (UnsupportedEncodingException ex) {
                        System.out.println("ERROR: " + ex.getMessage());
                    }
                }
            }
        );
        
        //hide the save button
        savebutton.setVisible(false);
        
        //add the buttons to the panel
        this.add(savebutton);
        this.add(newbutton);
        this.add(previousbutton);
        this.add(nextbutton);
        this.add(deletebutton);
        this.add(updatebutton);
    }
    
    /**
     * Switches the JList to the next record
     * 
     */
    private void switchToNext()
    {   
        //if at the last record
        if(list.getSelectedIndex() + 1 > list.getModel().getSize() - 1)
        {
            //Then go to the begenning
            list.setSelectedIndex(0);
        }
        else
        {
            //otherwise to to the next.
            list.setSelectedIndex(list.getSelectedIndex() + 1);
        }
                    
        //Update the contact pane
        contactdatapane.populateTextBoxesWithRecord(list.getSelectedValue().toString()); 
        list.ensureIndexIsVisible(list.getSelectedIndex());
    }
    
    /**
     * Switches the JList to the previous record.
     * 
     */
    private void switchToPrevious()
    {
        //If no record is selected
        if(list.getSelectedIndex() == -1)
        {
            list.setSelectedIndex(0);
        }
        
        //If at the first record
        if(list.getSelectedIndex() == 0)
        {
            //goto the last record
            list.setSelectedIndex(list.getModel().getSize() - 1);
        }
        else
        {
            //otherwise goto the previous record.
            list.setSelectedIndex(list.getSelectedIndex() - 1);
        }
        
        //Update the contact pane.
        contactdatapane.populateTextBoxesWithRecord(list.getSelectedValue().toString());
        list.ensureIndexIsVisible(list.getSelectedIndex());
    }
    
    /**
     * Redraws the parent frame to fix a small graphics bug when hitting 
     *  the new button for the first time. This bug only happens when the JFRame is
     *  small enough for the buttons to be close to the JScrollPanel
     * 
     */
    private void redrawParentFrame()
    {
        //get the Jframe that we are in
        JFrame frame = (JFrame) SwingUtilities.getRoot(this);
        //repaint the frame.
        frame.repaint();
    }
    
    /**
     * Checks to see if the Previous and Next buttons should be enabled based on 
     * the number of contact records.
     * 
     */
    private void shouldEnablePrevAndNext()
    {
        if(addressbook.getNames().size() > 1)
        {
            nextbutton.setEnabled(true);
            previousbutton.setEnabled(true);
        }
        else
        {
            nextbutton.setEnabled(false);
            previousbutton.setEnabled(false);
        }
    }
    
    /**
     * Checks to see if the delete button should be enabled based on 
     * the number of contact records.
     * 
     */
    private void shouldEnableDelete()
    {
        if(addressbook.getNames().size() > 0)
        {
            deletebutton.setEnabled(true);
        }
        else
        {
            deletebutton.setEnabled(false);
        } 
    }
}
