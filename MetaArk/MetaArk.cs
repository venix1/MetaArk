using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using MongoDB.Bson;
using MongoDB.Driver;

namespace MetaArk
{
    public class MetaArk
    {
        public delegate float StructureDamageHandler(object sender, float damage);

        event StructureDamageHandler OnStructureDamageEvent;

        public static MetaArk instance;

        private Random rnd;

        private MongoDB.Driver.MongoClient mClient;
        
        public MetaArk()
        {
            instance = this;
            rnd = new Random();

            mClient = new MongoDB.Driver.MongoClient("mongodb://localhost:27017");

            OnStructureDamageEvent += delegate (object sender, float damage)
            {
                var Database = mClient.GetDatabase("MetaArk");
                var collection = Database.GetCollection<MongoDB.Bson.BsonDocument>("config");
                var filter = Builders<BsonDocument>.Filter.Eq("key", "StructureDamage");
                var document = collection.Find(filter).FirstAsync().Result;

                bool doDamage = document.GetElement("value").Value.AsBoolean;

                if (doDamage)
                    return (float) rnd.NextDouble()*100;
                else
                    return 0;
            };
        }

        public float DoStructureDamage(float damage)
        {
            if (OnStructureDamageEvent != null)
                return OnStructureDamageEvent(this, damage);
            return damage;
        }
    }
}