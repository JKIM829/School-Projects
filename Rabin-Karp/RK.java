package rabinkarp;

public class RK {
	private int q;
	private int[] buffer= new int[q];	
	private int tracker=0;
	private int exponent = 0;
	private int h = 0;
	
	/**
	 * Rabin-Karp string matching for a window of the specified size
	 * @param m size of the window
	 */
	public RK(int m) {			//instantiating the circular buffer takes O(m) time because of expon(m) //Couldn't find any other way to calculate the exponent with mod without recursive method
		this.buffer = new int[m];
		this.exponent = expon(m);
	}
	

	/**
	 * Compute the rolling hash for the previous m-1 characters with d appended.
	 * @param d the next character in the target string
	 * @return
	 */
	public int expon(int n){	//this recursive formula takes O(m) time, to calculate the exponent 31^m with mod
		if(n==0){
			return 1;
		}
		else{
			return (31* (expon(n-1)%511))%511;
		}
	}
	
	public int nextCh(char d) {	//this method takes 0(1) time, since it only calls on variables already calculated.
		int mod = 511;
		int length = buffer.length;
		
		int c = buffer[tracker % (length)];	//get oldest element
		buffer[tracker % (length)] = d;	//add new element to the oldest element's place
		tracker++;	
		
		int first = (h*31)%mod;
		int second = exponent * (c%mod);
		int third = d%mod;
		h = (first - second%mod + third)%mod;	//h is always less than 511 and greater than -511. Modify h below for positive val
		
		if(h>=0){
			return h;
		}
		else{	//cases where remainders ends up negative, add 511 to make positive.
			h=(h+mod); //when h is negative, it'll never be less than -511, so no need to mod
			return h;
		}
	}

}
