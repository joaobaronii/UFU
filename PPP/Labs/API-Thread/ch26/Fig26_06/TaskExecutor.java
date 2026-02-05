// Fig. 26.6: TaskExecutor.java
// Using an ExecutorService to execute Runnables.
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;

public class TaskExecutor
{
   public static void main( String[] args )
   {
      // create and name each runnable
      PrintTask2 task1 = new PrintTask2( "task1" );
      PrintTask2 task2 = new PrintTask2( "task2" );
      PrintTask2 task3 = new PrintTask2( "task3" );
        
      System.out.println( "Starting Executor" );

      // create ExecutorService to manage threads
      ExecutorService threadExecutor = Executors.newCachedThreadPool();

      // start threads and place in runnable state
      threadExecutor.execute( task1 ); // start task1	
      threadExecutor.execute( task2 ); // start task2
      threadExecutor.execute( task3 ); // start task3

      // shut down worker threads when their tasks complete
      threadExecutor.shutdown(); 

      System.out.println( "Tasks started, main ends.\n" );
   } // end main
} // end class TaskExecutor