/**
 * @author TuckerFerguson
 * Date: October 18, 2018
 */
public class ThreadAccess extends Thread {
    
    private FileAccess monitor;
    private int pid;

    public ThreadAccess(int pid, FileAccess monitor) 
    {
        this.pid = pid;
        this.monitor = monitor;
    }

    @Override
    public void run() 
    {
        try 
        {
            Thread.currentThread().setName(pid + "");
            monitor.StartAccess();
            Thread.sleep(1000);
            monitor.EndAccess();
        } catch (InterruptedException ex) 
        {
            System.err.println("An error has occurred");
        }
    }
}