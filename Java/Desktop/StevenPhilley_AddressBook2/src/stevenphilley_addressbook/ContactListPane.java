package stevenphilley_addressbook;

import javax.swing.JList;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
/**
 * Pane to hold the contact list.
 * 
 * @author    Steven Philley
 * @version   2014-12-06
 */
@SuppressWarnings("serial")
public class ContactListPane  {
    
    private final JScrollPane scrollpane;
    private final AddressBook addressbook;
    private final JList nameslist;
    private ContactDataPane contactdatapane;
    
    public JScrollPane getScrollPane()
    {
        return scrollpane;
    }
    
    /**
     * Set the list for the list pane
     * 
     * @param inaddressbook
     */
    public ContactListPane(AddressBook inaddressbook)
    {   
        addressbook = inaddressbook;
        
         //Create a JList of the names in the addressbook
        nameslist = new JList<>(inaddressbook.getNames().toArray());
        //nameslist.setListData(this.getNames().toArray());
        nameslist.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
        nameslist.setLayoutOrientation(JList.VERTICAL);
        nameslist.setVisibleRowCount(-1);
        nameslist.setSelectedIndex(0);
        
        nameslist.addListSelectionListener(new ListSelectionListener(){

            @Override
            public void valueChanged(ListSelectionEvent e) {
                System.out.println(nameslist.getSelectedIndex() + ": " + nameslist.getSelectedValue());
                contactdatapane.clearTextBoxes();
                contactdatapane.populateTextBoxesWithRecord(nameslist.getSelectedValue().toString());
            }
        });
        
        scrollpane = new JScrollPane(nameslist);
    }
    
    /**
     * Return the list of names in natural order as an JList, this will
     *  always update the list first before returning it.
     * 
     * @return - the updated names list returned as a JList
     */
    public JList getNamesList()
    {   
        //first make sure the nameslist is update to date.
        updateNamesList("");
        
        return nameslist;
    }
    
    public void setContactDataPane(ContactDataPane incontactdatapane)
    {
        contactdatapane = incontactdatapane;
    }
        
    /**
     * Add or remove a name from the nameslist.
     * 
     * @param type 
     */
    public void updateNamesList(String type)
    {
        try
        {
            int index = nameslist.getSelectedIndex();
            
            nameslist.setListData(addressbook.getNames().toArray());
         
            if(type.toLowerCase().equals("delete"))
            {
                //If we deleted a record that is the first record
                if(index == 0)
                {
                    //then set to the first record
                    nameslist.setSelectedIndex(0);
                }
                else
                {
                    //otherwise just select the previous record
                    nameslist.setSelectedIndex(index-1);
                }
            }
            else
            {
                nameslist.setSelectedIndex(index);
            }
        }
        catch (Exception e)
        {
            System.out.println("WARNING: updateNamesList() - : " + e.getMessage());
        }
    }
}
