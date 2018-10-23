/**
 * @author TuckerFerguson
 * Date: October 18, 2018
 */
import java.util.Random;
import java.util.ArrayList;
import java.util.List;

public class monitorDriver {

    private static FileAccess monitor;
    private static final int MAX_THREADS = 32;
    
    
    public static void main(String[] args) throws InterruptedException 
    {
        if (args.length != 3)
        {
            System.err.println("Usage: java monitorDriver <numThreads> <max Sum> <iterations> ");
            System.exit(1);
        }
        
        int max = Integer.parseInt(args[0]);
        monitor = new FileAccess(max);
        Random rand = new Random(max);
        
        List<Thread> threads = new ArrayList<>();
        for (int i = 0; i < MAX_THREADS; ++i)
        {
           Thread ThreadAccess = new ThreadAccess(rand.nextInt(max), monitor);
           threads.add(ThreadAccess);
           ThreadAccess.start();
        }
        
        for (Thread thread : threads)
        {
            thread.join();
        }
    }
}