/**
 * @author TuckerFerguson
 * Date: October 18, 2018
 */
public class FileAccess{
    
    int total;
    int max;
    
    public FileAccess(int max)
    {
        this.max = max;
        this.total = 0;
    }
    
    public synchronized void StartAccess() throws InterruptedException
    {
        int pid = returnPid();
        if (!(pid > max))
        {
            while (total + pid > max)
            {
                this.wait();
            }
            System.out.println(String.format("Thread %d starting file access.", pid));
            this.total += pid;
        }
        
    }
    
    public synchronized void EndAccess()
    {
        int pid = returnPid();
        System.out.println(String.format("Thread %d ending file access.", pid));
        this.total -= pid;
        this.notifyAll();
    }
    
    public int returnPid()
    {
        return Integer.parseInt(Thread.currentThread().getName());
    }
}