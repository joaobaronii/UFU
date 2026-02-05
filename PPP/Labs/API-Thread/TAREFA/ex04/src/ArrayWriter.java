import java.lang.Runnable;
import java.util.Random;


public class ArrayWriter implements Runnable
{
   private final SimpleArray sharedSimpleArray;
   private final int startValue;
   private final static Random generator = new Random();
   
   public ArrayWriter( int value, SimpleArray array )
   {
      startValue = value;
      sharedSimpleArray= array;
   } // end constructor

   public void run()
   {
      for ( int i = startValue; i < startValue + 3; i++ )
      {   
          try
          {
             // put thread to sleep for 0-499 milliseconds
             Thread.sleep( generator.nextInt( 50 ) ); 
          } // end try
          catch ( InterruptedException ex )
          {
             ex.printStackTrace();
          } // end catch 
         sharedSimpleArray.add( i ); // add an element to the shared array
      } // end for
   } // end method run
} // end class ArrayWriter

