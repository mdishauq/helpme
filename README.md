# helpme
# 🚨 Need Help with STM32 Bare-Metal Project 🚨

Hi everyone! 👋  
I'm currently working on an STM32 bare-metal project and I'm facing some issues I haven't been able to resolve on my own. I'm sharing this repository in hopes that someone with experience can guide me in the right direction.

---

## 📌 Problem Summary

I'm trying to make the onboard LED on PC13 **blink using ADC** im using inbuilt temperature sensor, but the LED stays **constantly ON** instead of blinking.  
When I use simple LED blink code without ADC, it works fine.

---

## 📋 What I’ve Tried

- Verified GPIO setup works by running basic LED blink code ✅
- Checked ADC configuration ✅
- Reduced delay times to verify blink visibility ✅
- Tested on real hardware ✅

Despite all that, the LED doesn’t blink properly when ADC interrupt is enabled.

---

## 🧠 What I'm Looking For

- Guidance on setting up ADC correctly.
- Tips on debugging in STM32.
- Review of my code to find potential issues.

---

## 🙏 How You Can Help

1. Clone the repo
2. Review the `main.c` and interrupt setup
3. Suggest corrections or improvements via:
   - Issues
   - Pull requests
   - Discussions

---

## 💬 Contact or Discussion

Feel free to open an [Issue](https://github.com/yourusername/your-repo-name/issues) or comment directly on the code.  
If you want to discuss it in real-time, ping me and I can join Discord/Reddit/etc.

Thanks in advance to everyone taking the time to help! ❤️

