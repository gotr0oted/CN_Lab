# Practical 7: Application Protocol Analysis with Wireshark

## Aim
Capture application-layer traffic and inspect the transport and network headers carrying it.

## Procedure
1. Select your active interface and start a Wireshark capture.
2. Generate permitted traffic: perform a DNS lookup or visit a website.
3. Stop the capture. Try display filters `dns`, `tcp`, `http`, and `tls`.
4. Expand Ethernet, IP, TCP/UDP, and application protocol details in a selected packet.
5. Record addresses, ports, protocol, and fields visible in the packet.

## Notes and result
HTTPS payload is encrypted; packet analysis can show connection metadata and TLS records, not protected page contents. Capture only traffic you are authorized to inspect. Summarize a DNS exchange and a TCP/TLS flow from your own capture and include your own screenshot if required.

The attached `demo-capture.pcapng` is a Codex-run loopback demonstration of the repository's TCP and UDP echo programs. It is not evidence that the student personally performed the experiment; create your own capture for submission.
