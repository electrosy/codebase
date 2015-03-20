/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package stevenphilley_addressbook;

import java.util.Comparator;

/**
 * Comparator to ignore case on the strings.
 * 
 * @author Steven Philley
 * @version 2014-09-28
 */
public class StringIgnoreCaseComparator implements Comparator<String> {

    @Override
    public int compare(String o1, String o2) {
        return o1.toLowerCase().compareTo(o2.toLowerCase());
    }
}
