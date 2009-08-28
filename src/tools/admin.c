/**
 * A remote uhub admin client.
 */

#include "adcclient.h"

static int handle(struct ADC_client* client, enum ADC_client_callback_type type, struct ADC_client_callback_data* data)
{
	switch (type)
	{
		case ADC_CLIENT_CONNECTING:
			puts("*** Connecting...");
			break;

		case ADC_CLIENT_CONNECTED:
			puts("*** Connected.");
			break;

		case ADC_CLIENT_DISCONNECTED:
			puts("*** Disconnected.");
			break;

		case ADC_CLIENT_LOGGING_IN:
			puts("*** Logging in...");
			break;

		case ADC_CLIENT_PASSWORD_REQ:
			puts("*** Requesting password.");

		case ADC_CLIENT_LOGGED_IN:
			puts("*** Logged in.");
			break;

		case ADC_CLIENT_LOGIN_ERROR:
			puts("*** Login error");
			break;

		case ADC_CLIENT_MESSAGE:
			printf("    <%s> %s\n", sid_to_string(data->chat->from_sid), data->chat->message);
			break;

		case ADC_CLIENT_USER_JOIN:
			break;

		case ADC_CLIENT_USER_QUIT:
			break;

		case ADC_CLIENT_SEARCH_REQ:
			break;

		case ADC_CLIENT_HUB_INFO:
			printf("    Hub: \"%s\" [%s]\n"
				   "         \"%s\"\n", data->hubinfo->name, data->hubinfo->version, data->hubinfo->description);
			break;

		default:
			printf("Not handled event=%d\n", (int) type);
			return 0;
			break;
	}
	return 1;
}


int main(int argc, char** argv)
{
	struct ADC_client client;
	net_initialize();

	ADC_client_create(&client, "uhub-admin", "stresstester");
	ADC_client_set_callback(&client, handle);
	ADC_client_connect(&client, "adc://adc.extatic.org:1511");

	event_dispatch();

	ADC_client_destroy(&client);
	net_destroy();
	return 0;
}


