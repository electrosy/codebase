package stevenphilley_addressbook;

import java.util.HashMap;

/**
 * Representation of a single contact record which is an arbitrary number 
 * of name value pairs.
 * 
 * @author    Steven Philley
 * @version   2014-12-06
 */
public class ContactData 
{
    private final HashMap<String, String> contactdata;
    
    /**
     * Create a String String key value pair.
     * 
     */
    public ContactData()
    {
        contactdata = new HashMap<String, String>();
    }
    
    /**
     * Set the value of a field
     * 
     * @param field
     * @param value 
     */
    public void setValue(String field, String value)
    {
        contactdata.put(field, value);
    }
    
    /**
     * Retrieve the value of a specific field.
     * 
     * @param field The name of the field to retrieve the value of.
     * @return The value for the field passed in.
     */
    public String getValue(String field)
    {
        return contactdata.get(field);
    }
    
    /**
     * A convenience method to retrieve two values separated by 
     * a specified character.
     * 
     * @param infirst - The name of the first field to retrieve
     * @param insecond - The name of the second field to retrieve
     * @param insaprator - Separator character.
     * @return The first and second value separated by the third string passed in.
     */
    public String getKeyPairValue(String infirst, String insecond, String inseparator)
    {
        try
        {            
            return contactdata.get(infirst) + inseparator + contactdata.get(insecond);
        }
        catch (java.lang.NullPointerException exception)
        {
            System.out.print("FATAL: " + exception.getMessage());
            return null;
        }
    }
}