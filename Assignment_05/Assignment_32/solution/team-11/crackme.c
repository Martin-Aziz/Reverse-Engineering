#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define KEY "THERE IS AN EASIER WAY THAN TO REVERSE THE WIN FUNCTION"

int close_wizard(void) {
  printf("\n\n%s\n", "Thank you for using HyperCam 2. Exiting...");
  exit(0);
}

int check_success(void) {
  printf("%s\n", "While the license may be valid, we detected that it was obtained illegally!");
  // padding strings to move win function into ASCII-printable range (making the crackme easier to solve)
  char padstr1[] = "qZiaIIAPWTvmRhUBjNTKWcGiKjOItademGmUGyBGrJvegXQSWhssUnuQRVOaAMEXOQrFRpqiwWStGlJtsZAKthcJTwDJBlayDnIU";
  char padstr2[] = "tdlAFjpZywaIEGUkPbpqrgocrpPsNPtlPfEcgKIMIByJtsOkWmyqWvlqsfZZficgjVsZUJosPUWZzVsGhEGjnvssGNqopJhLHqVB";
  char padstr3[] = "ApFzfppxRmMTdmeDHggMOEesigSleXmuHksJuTteBiLUdJWMrWnRbBKZEQebGTVEnCqCZdjLawOGeiNtNlxeiNeUGVEIkMQRfPSv";
  char padstr4[] = "lywtheWwmfDNiIBFQUoCXiuRCdyOwcEDPJaSjSZQzLXZkldWlILHGZIbwbIMKGfUDhcMrrhudzUfTYTzbeZFNiurbPlLpwJUgUSx";
  char padstr5[] = "tFbHuMfgApxrbVQzddVhOXgsqvITctRiGnuvsnSAznMOMqSCqlulGXMNZavwQVfHqTJHqMEpwRxJwkECNBoNzVtRwbWvtRFUeXSO";
  char padstr6[] = "HZwfTYqzpqCXjaReQuBNliMtcXAuGiYLZgLnVEBdvcWjorbWwRzTiLEsuChhazQaIprXuKLZCtjFXgTwdIDlTVFVfnoMwvVvJRgV";
  char padstr7[] = "geVHOKLmFxXccsZlnkroWoRRjfcKywLcFaLAJAFIbeBQpiFloQrTfOWJyCJQAWXSqsBalhBHIFObCFeaNZyccyaUUVDALLtUfYkw";
  char padstr8[] = "bfUEiCekbplMyUTjaMWkbMWjdcRfkkpRlhCSAmHONGsPZcnDvgnrNqzyeWrJqBfGHoSUFmsEkliLLntgVPutMLjFFKmazPTejnJh";
  char padstr9[] = "CwCGPYlTYxIECFsHFGJyDjOqLLEGkBVTBZacCGRJKoyaDDWvLxHHAiBjYUaiijZlHipkJbCSNBFtfNTiGgoNmYccXvwOFwDZTmgQ";
  char padstr10[] = "CVdzKXUUzyJAobqBjOetXLbfrhstHaTyGZrBNPSDVbjGBMdVRrwJitVrIigymvvgSFreAtVWzZZVbMmNwnGEzGnxeVGKzHZgpGbr";
  char padstr11[] = "wIAdBsKwVGIUbdTCtcdBfPcCbjARNJxLGRAZhkoXPKuglduxZIdvitAmQZmNYAScNKflyXErtFVsuemrrSpXUVdgmmtMyhUfelRk";
  char padstr12[] = "NYUxTTEvNLfvWekwRvaPKzxcnFRZNiwAHPUFPRQDjUuwoxddjjhmeOQxVDNqmQclPnOeAXMHmYcVIPHYvCYCbYNjzmzfWmCCftRd";
  char padstr13[] = "aDcexpyfSuAYpvAbepWVIoHsZQxIxSBJLSimuQdqQTzXOicSTFjYKXfqJyWibUyAzxjVVxUFgsrmCPyqfKTUjSBFhboNKiYLTJCI";
  char padstr14[] = "QWCstYynxNEzSQXAqdifHjbNgvvQsORjQqKQMsJprCayPGDSbRQKyMClQuTpmhWgLRGGhPIahRfrWncOjRzWCPQSFGNSLmTYArCM";
  char padstr15[] = "oOdIrkOKxnkFmQNLzsGHwwSJiLebdKvBDGznJWTvHKlQYlUIOyBSFNXJEHwezrDYPiHFSvZBxjZGSsALZzzqmyyoseUVHdxMZEmQ";
  char padstr16[] = "GLZETpYyYnYwdnPLGMHaGTsXLPVMkFIcDtIOQsFXNtPDokWhAnocCDGspmatoyGtGqzuqkclhxvEiRusHWfsTSFhlSSZZxvZEEdD";
  char padstr17[] = "AIGpqzkZamfPlxzEinIMCrNUpwvyYQSDnbIKqqMoYONcMhfCjnMPaaNHGonvidKTttDkREETrsjZaIkzQhcYAlSeRoKJyBHvBEKm";
  char padstr18[] = "LDFEqDrjsCcDiuOIYmUbJjzclIGLUFROkIpYawHAMGDxcFCKwWdXciofMjKJfOgKheIgvJzLNwFuHITWzPyfOTZfGfmafDxDSWpR";
  close_wizard();
}

int win(void) {
 unsigned char s[] = {
    0x07, 0xfa, 0xbe, 0xa5, 0x28, 0xc1,
    0x9b, 0x21, 0x71, 0x89, 0xda, 0x24,
    0x0c, 0x7f, 0x68, 0x5e, 0xc6, 0x5a,
    0x64, 0x96, 0x59, 0x85, 0xb4, 0x13,
    0xff, 0x59, 0x3d, 0xec, 0x6d, 0xbb,
    0x2d, 0x15, 0xe4, 0xac
  };

  for (int i = 0; i < strlen(s); i++) {
    s[i] ^= KEY[i];
  }

  for (unsigned int i = 0; i < sizeof(s); ++i) {
    unsigned char res = s[i];
    res -= i;
    res ^= 0xb1;
    res = (res >> 0x1) | (res << 0x7);
    res -= 0xae;
    res = (res >> 0x6) | (res << 0x2);
    res ^= i;
    res = ~res;
    res = (res >> 0x6) | (res << 0x2);
    res ^= i;
    res += 0x43;
    res = (res >> 0x2) | (res << 0x6);
    res += 0xce;
    res = -res;
    res ^= i;
    res -= 0x91;
    res = (res >> 0x3) | (res << 0x5);
    res -= 0x55;
    res = -res;
    res += i;
    res = -res;
    res = ~res;
    res += 0xbe;
    res = -res;
    res += 0x7e;
    res = -res;
    res = (res >> 0x6) | (res << 0x2);
    res ^= 0x4;
    res -= i;
    s[i] = res;
  }

  printf("Successfully registered HyperCam 2. Your current license-key is: %s\n", s);
  close_wizard();
}

int main(void) {
  // Init: Allocating Buffer, setting up method pointer
  char buf[128];
  volatile int(*fp)() = &check_success;

  // Calculating the "secret" (the license)
  char secret[] = {0x25, 0x26, 0x20, 0x2a, 0x2c, 0x27, 0x3a, 0x2c};
  for (int i = 0; i < sizeof(secret); i++) {
    secret[i] ^= 0x69;
  }

  // Greetings
  printf("%s\n", "+-----+ Welcome to the 'HyperCam 2' registration wizard! +-----+");
  printf("%s\n", "Checking license status...");
  sleep(1);
  printf("%s\n", "Your current license status: 'Unregistered HyperCam 2'");
  printf("%s", "Please enter a valid license key: ");

  // Read user input with gets
  gets(buf);

  if (strncmp(buf, secret, 5) == 0) {
    printf("\nExecuting license check: 0x%08x...\n", fp);
    fp();
  } else {
    printf("%s\n", "Invalid license key!");
  }
  close_wizard();
}
