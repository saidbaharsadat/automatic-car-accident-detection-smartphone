// Reconstructed and sanitized from the thesis code excerpt.
// This is documentation of the original prototype logic, not a complete app service.

using Firebase.Database;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Threading.Tasks;

namespace Hadisa.Services
{
    public class FirebaseRTBService
    {
        private readonly FirebaseClient firebaseClient;

        public FirebaseRTBService(string databaseUrl)
        {
            firebaseClient = new FirebaseClient(databaseUrl);
        }

        public async Task SendOperationDataLocationOnly(
            string operationId,
            string latitudeKey,
            string longitudeKey,
            string latitude,
            string longitude)
        {
            JObject payload = new JObject
            {
                { latitudeKey, latitude },
                { longitudeKey, longitude }
            };

            await firebaseClient
                .Child("Acident Operation" + "/" + operationId + "/")
                .PatchAsync(JsonConvert.SerializeObject(payload));
        }

        public async Task UpdateAccidentStatus(string status, string operationId)
        {
            await firebaseClient
                .Child("Acident Detected" + "/" + operationId + "/Status/")
                .PutAsync(JsonConvert.SerializeObject(status));
        }

        public async Task DeleteAccident(string accidentId)
        {
            await firebaseClient
                .Child("Acident Detected" + "/" + accidentId + "/")
                .DeleteAsync();
        }
    }
}
