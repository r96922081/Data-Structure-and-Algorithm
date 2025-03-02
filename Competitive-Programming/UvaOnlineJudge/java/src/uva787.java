import java.io.FileInputStream;
import java.io.InputStream;
import java.io.PrintStream;
import java.math.BigInteger;
import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Scanner;

public class uva787 {

    public static void main (String args[])  // entry point from OS
    {
        String host_name = "Unknown";

        try
        {
            InetAddress addr;
            addr = InetAddress.getLocalHost();
            host_name = addr.getHostName();
        }
        catch (UnknownHostException ex)
        {
        }        
        
        int io_choice = 1;
        
        if (host_name.equals("VAIO"))
            io_choice = 2;
        
        InputStream input_stream = null;
        PrintStream output_stream = null;
        
        if (io_choice == 1)
        {
            input_stream = System.in;
            output_stream = System.out;
        }
        else
        {
            try
            {
                input_stream = new FileInputStream("input.txt");
                output_stream = new PrintStream("myoutput.txt");
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }
        }
        
        algorithm(input_stream, output_stream);
    }    
    
    public static void algorithm(InputStream input_stream, PrintStream output_stream)
    {
        Scanner input = new Scanner(input_stream);

        while (true)
        {
            if (input.hasNext() == false)
                return;
             
            ArrayList<Integer> number_array = new ArrayList<Integer>();
            int next_int = input.nextInt();
            while (next_int != -999999)
            {
                number_array.add(next_int);
                next_int = input.nextInt();
            }
                
            BigInteger max_product = new BigInteger(number_array.get(0).toString());
            BigInteger min_negative_suffix = new BigInteger("0");
            BigInteger max_positive_suffix = new BigInteger("0");
            BigInteger zero = new BigInteger("0");
                
            for (int number_int : number_array)
            {
                BigInteger number = new BigInteger(String.valueOf(number_int));
                BigInteger new_product;
                
                if (number.compareTo(zero) > 0)
                {
                    if (max_positive_suffix.compareTo(zero) == 0)
                    {
                        new_product = new BigInteger(String.valueOf(number_int));
                        max_positive_suffix = new BigInteger(String.valueOf(number_int));
                    }
                    else
                    {
                        new_product = max_positive_suffix.multiply(number);
                        max_positive_suffix = max_positive_suffix.multiply(number);
                    }
                    
                    min_negative_suffix = min_negative_suffix.multiply(number);
                }
                else if (number.compareTo(zero) < 0)
                {
                    BigInteger new_max_positive_suffix = min_negative_suffix.multiply(number);

                    if (min_negative_suffix.compareTo(zero) == 0)
                    {
                        new_product = new BigInteger(String.valueOf(number_int)); 
                    }
                    else
                    {
                        new_product = min_negative_suffix.multiply(number); 
                    }
                    
                    if (max_positive_suffix.compareTo(zero) == 0)
                    {
                        min_negative_suffix = new BigInteger(String.valueOf(number_int));  
                    }
                    else
                    {
                        min_negative_suffix = max_positive_suffix.multiply(number); 
                    }
                    
                    max_positive_suffix = new_max_positive_suffix;                    
                }
                else
                {
                    max_positive_suffix = new BigInteger(String.valueOf(0));
                    min_negative_suffix = new BigInteger(String.valueOf(0));
                    new_product = new BigInteger(String.valueOf(0));                  
                }
                
                if (new_product.compareTo(max_product) > 0)
                    max_product = new_product;                 
            }
                           
            output_stream.println(max_product);
        }    
    }
}
