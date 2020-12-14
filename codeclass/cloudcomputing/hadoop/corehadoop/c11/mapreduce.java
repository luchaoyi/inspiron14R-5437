//基类Mapper,自己的实现需要继承hadoop的Mapper
public class Mapper<KEYIN,VALUEIN,KEYOUT,VALUEOUT>{
	//map前调用
	protected void setup(Context context) throws IOException,InterruptedException{
		//...
	}

	protected void map(KEYIN key,VALUEIN value,Context context) throws IOException,InterruptedException{
		contex.write((KEYOUT) key,(VALUEOUT) value);
	}

	protected void cleanup(Context context) throws IOException,InterruptedException{
		//...
	}

	public void run(Context context) throws IOException,InterruptedException{
		setup(context);
		try{
			while(context.nextKeyValue()){
				map(context.getCurrentKey(),context.getCurrentValue(),context);
			}
		}finally{
			cleanup(Context);
		}
	}
}

//Reducer类似,用户一般重载reduce函数

public class MyDriver{
	public static void main(String[] args) throws Exception {
		Configuration conf = new Configuration(); //读取配置
		String[] otherArgs=new GenericOptionsParaser(conf,args).getRemainingArgs();
		if(otherArgs.length!=2){
			System.err.println("Usage:wordcount <in> <out>");
			System.exit(2);
		}
		Job job=new Job(conf,"word count");//job name is word count 

		//驱动类
		job.setJarByClass(MyDriver.class);
		//job.setMapperClass
		//job.setCombinerClass
		//job.setReducerClass
		//job.set*
		//...
		FileInputFormat.addInputPath(job,new Path(otherArgs[0]));
		FileInputFormat.addOutputPath(job,new Path(otherArgs[0]));
		System.exit(job.waitForCompletion(true)? 0:1); //提交作业，等待运行完成返回

	}
}

