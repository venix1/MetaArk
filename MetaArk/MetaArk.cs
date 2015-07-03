using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using MongoDB.Bson;
using MongoDB.Driver;
using System.IO;

namespace MetaArk
{
    public class Config
    {
        public string connectionString { get; set; }
    }

    public class MetaArk
    {
        public delegate float StructureDamageHandler(object sender, float damage);

        event StructureDamageHandler OnStructureDamageEvent;

        public static MetaArk instance;

        private Random rnd;

        private MongoDB.Driver.MongoClient mClient;

        public Config mConfig;
        
        public MetaArk()
        {
            instance = this;
            rnd = new Random();

            var input = new StreamReader("MetaArk.yaml");
            var yaml = new YamlDotNet.Serialization.Deserializer();
            mConfig = yaml.Deserialize<Config>(input);
            mClient = new MongoDB.Driver.MongoClient(mConfig.connectionString);

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