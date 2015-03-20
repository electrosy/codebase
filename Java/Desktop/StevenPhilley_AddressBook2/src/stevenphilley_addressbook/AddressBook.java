package stevenphilley_addressbook;

import edu.frontrange.csc241.a5.input.InputData;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Map;
import java.util.TreeMap;

/**
 * An Address book has a set of contactdatas.
 * 
 * @author    Steven Philley
 * @version   2014-12-06
 */
public final class AddressBook 
{
    private final TreeMap<String, ContactData> contacts;
    private final ArrayList<String> fieldnames;
    
    public AddressBook()
    {
        //create the TreeMap
        contacts = new TreeMap<String, ContactData>(new StringIgnoreCaseComparator());

        //A list of fields to be used with the address book.
        fieldnames = new ArrayList<String>();
        //Set the field names
        fieldnames.add("First Name");
        fieldnames.add("Last Name");
        fieldnames.add("City");
        fieldnames.add("State");
        fieldnames.add("Zip");
        fieldnames.add("Address1");
        fieldnames.add("Address2");
        
        loadContactDataFromFile();
    }
    
    /**
     * return the possible fieldnames
     * 
     * @return 
     */
    public ArrayList<String> getFields()
    {
        return fieldnames;
    }
    /**
     * Update a contact in the address book.
     * 
     * @param contact
     * @return 
     */
    public boolean updateContact(ContactData contact)
    {       
        String key = contact.getKeyPairValue("First Name", "Last Name", " ");
        
        removeContact(key);
        
        return contacts.put(key, contact) == null;
    }
    
    /**
     * Add a contact to the address book.
     * 
     * @param contact
     * @return 
     */
    public boolean addContact(ContactData contact)
    {
        String firstname = contact.getValue("First Name");
        String lastname = contact.getValue("Last Name");
        
        return contacts.put(firstname + " " + lastname, contact) == null;
    }
    
    /**
     * Return the list of names
     * 
     * @return - the names in the contact records
     */
    public ArrayList<String> getNames()
    {
        ArrayList<String> names = new ArrayList<String>();
        
        for(Map.Entry<String,ContactData> entry : contacts.entrySet()) 
        {
            names.add(entry.getKey());
        }
        
        return names;
    }
    
    /**
     * Gets a ContactData from the list of contacts.
     * 
     * @param contactnumber
     * @return 
     */
    public ContactData getContact(String key)
    {
        //if the key is not empty then return the specific record for key
        if(!key.isEmpty())
        {
            return contacts.get(key);
        }

        //by default return the first record
        //note: this value can be null
        return contacts.firstEntry().getValue(); 
    }
    
    /**
     * Removes a ContactData from the list of contacts.
     * 
     * @param key - contact record to remove
     * @return 
     */
    public void removeContact(String key)
    {
        contacts.remove(key);
    }
    
    private void loadContactDataFromFile()
    {
        //Read the data from the file. 
        final int VALUES_PER_INPUT_LINE = 7;

        try(InputData inputData = new InputData("addressdatafile.txt",
                        InputData.class, null, VALUES_PER_INPUT_LINE, ",") )
        {
            // For each row from the file
            for(String[] value : inputData )
            {
                    //Build a contact and add it to the addressbook.
                    ContactData tempcontact = new ContactData();

                    //For each field in the contact data
                    int i=0;
                    for(String s : fieldnames)
                    {
                        tempcontact.setValue(s, value[i++]);
                    }

                    addContact(tempcontact);
            }
        }
        catch(Exception e)
        {
            System.out.println("ERROR: File is empty or has invalid format. :" + e.getMessage());
        }
    }
    
    public void saveDataToFile() throws UnsupportedEncodingException
    {
        try 
        {
            PrintWriter writer = new PrintWriter(".\\src\\edu\\frontrange\\csc241\\a5\\input\\addressdatafile.txt", "UTF-8");

            //Loops through all the contacts
            for(Map.Entry<String,ContactData> entry : contacts.entrySet()) 
            {
                String datarow = new String();
                //names.add(entry.getKey());
                //Then loop through the possible fields
                for(String f : fieldnames)
                {
                    datarow += entry.getValue().getValue(f);
                    datarow += ","; // TODO shouldn't have the ',' at the end of the line.
                }
                
                System.out.println(datarow);
                writer.println(datarow);
            }
          
            writer.close();
        }
        catch (FileNotFoundException | UnsupportedEncodingException e)
        {
            System.out.println("ERROR: " + e.getMessage());
        }
    }
}
