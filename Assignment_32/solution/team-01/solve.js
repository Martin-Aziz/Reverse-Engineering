const { spawn } = require("child_process");
const readline = require("readline/promises");

function shuffle_reverse(password)
{
	let length = password.length;
	for (let i = length - 1; i >= 0; i--)
	{
		let j = ((i ^ (i << 1)) * 29) % length;
		let temp = password[i];
		password[i] = password[j];
		password[j] = temp;
	}
	return password;
}

main();
async function main()
{
	// stdbuf prevents buffering of the input and output streams preventing deadlocks if both programs wait for input which they never get because it is buffered.
	const child_process = spawn("stdbuf", ["-i0", "-o0", "-e0", "./crackme"]);
	const finished = new Promise(r => process.once("exit", r));
	child_process.stdout.pipe(process.stdout);
	const rl = readline.createInterface({ input: child_process.stdout, output: child_process.stdin });
	child_process.stdin.write(shuffle_reverse([..."index_shuffle"]).join("") + "\n");
	// writes to the output stream (which is the child processes input stream) and then reads one line from the input stream (the child processes output stream)
	const res = await rl.question("-1 15\n");
	const number = res.match(/(?<= )\d+$/)?.[0];
	child_process.stdin.write(`14 ${number}`);
	child_process.stdin.end();
	await finished;
}