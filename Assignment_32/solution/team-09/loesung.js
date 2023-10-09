const { spawn } = require("child_process");

main();
async function main()
{
	{
		console.log("Inputing: %j %j %j %j %j %j %m");
        console.log("Without ceaser encryption: %p %p %p %p %p %p %s");
		const check_process = spawn("./crackme_team09");
		check_process.stdout.pipe(process.stdout);
		check_process.stdin.write("%j %j %j %j %j %j %m");
		await new Promise(r => check_process.once("exit", r));
	}
    console.log();
}